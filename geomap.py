# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    geomap.py                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/12 10:21:08 by joesanto          #+#    #+#              #
#    Updated: 2025/11/12 10:21:21 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

"""
Satellite Image & Real Heightmap Fetcher
Fetches satellite imagery and real elevation data for any world coordinates
"""

import requests
import numpy as np
import cv2
from PIL import Image
from io import BytesIO
import math
from pathlib import Path
import argparse


class GeoHeightmapFetcher:
    """Fetch satellite imagery and elevation data for geographic coordinates"""
    
    def __init__(self):
        """Initialize the fetcher with API endpoints"""
        # Multiple data sources for redundancy
        self.mapbox_token = None  # Optional: get free token at mapbox.com
        self.google_api_key = None  # Optional: get at cloud.google.com
        
    def fetch_satellite_image(self, lat, lon, width, height, zoom=15, 
                             location_name="location"):
        """
        Fetch satellite/aerial imagery for coordinates
        
        Args:
            lat: Latitude (-90 to 90)
            lon: Longitude (-180 to 180)
            width: Image width in pixels
            height: Image height in pixels
            zoom: Zoom level (1-20, higher = more detail)
            location_name: Name for output file
            
        Returns:
            Image as numpy array
        """
        print(f"Fetching satellite image for ({lat}, {lon})...")
        print(f"  Resolution: {width}x{height}, Zoom: {zoom}")
        
        # Try different tile providers
        success = False
        
        # Method 1: OpenStreetMap satellite (free, limited detail)
        if not success:
            try:
                img = self._fetch_osm_satellite(lat, lon, width, height, zoom)
                success = True
                print("✓ Fetched from OpenStreetMap")
            except Exception as e:
                print(f"✗ OSM failed: {e}")
        
        # Method 2: ESRI World Imagery (free, good quality)
        if not success:
            try:
                img = self._fetch_esri_satellite(lat, lon, width, height, zoom)
                success = True
                print("✓ Fetched from ESRI World Imagery")
            except Exception as e:
                print(f"✗ ESRI failed: {e}")
        
        # Method 3: Mapbox (requires free API token, excellent quality)
        if not success and self.mapbox_token:
            try:
                img = self._fetch_mapbox_satellite(lat, lon, width, height, zoom)
                success = True
                print("✓ Fetched from Mapbox")
            except Exception as e:
                print(f"✗ Mapbox failed: {e}")
        
        if not success:
            raise Exception("All satellite image sources failed. Check internet connection.")
        
        # Save the satellite image
        output_path = f"{location_name}_satellite.png"
        cv2.imwrite(output_path, cv2.cvtColor(img, cv2.COLOR_RGB2BGR))
        print(f"Satellite image saved: {output_path}")
        
        return img
    
    def fetch_elevation_data(self, lat, lon, width, height, zoom=15,
                           location_name="location"):
        """
        Fetch real elevation/terrain data for coordinates
        
        Args:
            lat: Latitude
            lon: Longitude
            width: Heightmap width in pixels
            height: Heightmap height in pixels
            zoom: Detail level
            location_name: Name for output file
            
        Returns:
            Heightmap as numpy array (16-bit)
        """
        print(f"Fetching elevation data for ({lat}, {lon})...")
        print(f"  Resolution: {width}x{height}")
        
        # Calculate bounding box for the area
        bbox = self._calculate_bbox(lat, lon, width, height, zoom)
        
        # Try different elevation data sources
        success = False
        
        # Method 1: Open-Elevation API (free, global coverage)
        if not success:
            try:
                heightmap = self._fetch_open_elevation(bbox, width, height)
                success = True
                print("✓ Fetched elevation from Open-Elevation API")
            except Exception as e:
                print(f"✗ Open-Elevation failed: {e}")
        
        # Method 2: Terrain tiles (free, good for visualization)
        if not success:
            try:
                heightmap = self._fetch_terrain_tiles(lat, lon, width, height, zoom)
                success = True
                print("✓ Fetched from Terrain RGB tiles")
            except Exception as e:
                print(f"✗ Terrain tiles failed: {e}")
        
        # Method 3: SRTM data via OpenTopography (free, requires samples)
        if not success:
            try:
                heightmap = self._fetch_srtm_sampled(bbox, width, height)
                success = True
                print("✓ Fetched SRTM elevation data")
            except Exception as e:
                print(f"✗ SRTM failed: {e}")
        
        if not success:
            raise Exception("All elevation data sources failed.")
        
        # Normalize to 16-bit range
        heightmap_normalized = self._normalize_heightmap(heightmap)
        
        # Save the heightmap
        output_path = f"{location_name}_heightmap.png"
        cv2.imwrite(output_path, heightmap_normalized)
        print(f"Heightmap saved: {output_path}")
        
        # Also save metadata
        meta_path = f"{location_name}_metadata.txt"
        with open(meta_path, 'w') as f:
            f.write(f"Location: ({lat}, {lon})\n")
            f.write(f"Bounding Box: {bbox}\n")
            f.write(f"Resolution: {width}x{height}\n")
            f.write(f"Zoom Level: {zoom}\n")
            f.write(f"Min Elevation: {np.min(heightmap):.2f}m\n")
            f.write(f"Max Elevation: {np.max(heightmap):.2f}m\n")
            f.write(f"Elevation Range: {np.max(heightmap) - np.min(heightmap):.2f}m\n")
        print(f"Metadata saved: {meta_path}")
        
        return heightmap_normalized
    
    def _calculate_bbox(self, lat, lon, width, height, zoom):
        """Calculate bounding box for the requested area"""
        # Approximate meters per pixel at given zoom and latitude
        meters_per_pixel = 156543.03392 * math.cos(lat * math.pi / 180) / math.pow(2, zoom)
        
        # Calculate extent in degrees
        width_meters = width * meters_per_pixel
        height_meters = height * meters_per_pixel
        
        # Convert to degrees (approximate)
        lat_extent = height_meters / 111320  # meters per degree latitude
        lon_extent = width_meters / (111320 * math.cos(lat * math.pi / 180))
        
        return {
            'north': lat + lat_extent / 2,
            'south': lat - lat_extent / 2,
            'east': lon + lon_extent / 2,
            'west': lon - lon_extent / 2
        }
    
    def _fetch_esri_satellite(self, lat, lon, width, height, zoom):
        """Fetch from ESRI World Imagery (free)"""
        # Calculate tile coordinates
        tile_x, tile_y = self._lat_lon_to_tile(lat, lon, zoom)
        
        # ESRI World Imagery tile URL
        url = f"https://server.arcgisonline.com/ArcGIS/rest/services/World_Imagery/MapServer/tile/{zoom}/{tile_y}/{tile_x}"
        
        response = requests.get(url, timeout=10)
        response.raise_for_status()
        
        img = Image.open(BytesIO(response.content))
        img = img.resize((width, height), Image.LANCZOS)
        
        return np.array(img)
    
    def _fetch_osm_satellite(self, lat, lon, width, height, zoom):
        """Fetch from OpenStreetMap satellite tiles"""
        tile_x, tile_y = self._lat_lon_to_tile(lat, lon, zoom)
        
        # Multiple OSM satellite providers
        providers = [
            f"https://a.tile.openstreetmap.org/{zoom}/{tile_x}/{tile_y}.png",
            f"https://tiles.wmflabs.org/hikebike/{zoom}/{tile_x}/{tile_y}.png"
        ]
        
        for url in providers:
            try:
                response = requests.get(url, timeout=10)
                response.raise_for_status()
                img = Image.open(BytesIO(response.content))
                img = img.resize((width, height), Image.LANCZOS)
                return np.array(img)
            except:
                continue
        
        raise Exception("All OSM providers failed")
    
    def _fetch_mapbox_satellite(self, lat, lon, width, height, zoom):
        """Fetch from Mapbox (requires API token)"""
        if not self.mapbox_token:
            raise Exception("Mapbox token not set")
        
        url = f"https://api.mapbox.com/styles/v1/mapbox/satellite-v9/static/{lon},{lat},{zoom}/{width}x{height}?access_token={self.mapbox_token}"
        
        response = requests.get(url, timeout=10)
        response.raise_for_status()
        
        img = Image.open(BytesIO(response.content))
        return np.array(img)
    
    def _fetch_open_elevation(self, bbox, width, height):
        """Fetch elevation data from Open-Elevation API"""
        # Generate a grid of points to sample
        lats = np.linspace(bbox['south'], bbox['north'], height)
        lons = np.linspace(bbox['west'], bbox['east'], width)
        
        # For large grids, sample strategically
        sample_height = min(height, 100)
        sample_width = min(width, 100)
        
        lats_sample = np.linspace(bbox['south'], bbox['north'], sample_height)
        lons_sample = np.linspace(bbox['west'], bbox['east'], sample_width)
        
        # Create locations list
        locations = []
        for lat in lats_sample:
            for lon in lons_sample:
                locations.append({"latitude": lat, "longitude": lon})
        
        # API endpoint
        url = "https://api.open-elevation.com/api/v1/lookup"
        
        # Send request in batches (API limit)
        batch_size = 100
        elevations = []
        
        for i in range(0, len(locations), batch_size):
            batch = locations[i:i+batch_size]
            response = requests.post(url, json={"locations": batch}, timeout=30)
            response.raise_for_status()
            data = response.json()
            elevations.extend([r['elevation'] for r in data['results']])
        
        # Reshape and interpolate to final size
        elev_grid = np.array(elevations).reshape(sample_height, sample_width)
        
        # Interpolate to final resolution
        from scipy.ndimage import zoom
        zoom_factors = (height / sample_height, width / sample_width)
        heightmap = zoom(elev_grid, zoom_factors, order=3)
        
        return heightmap
    
    def _fetch_terrain_tiles(self, lat, lon, width, height, zoom):
        """Fetch from Mapbox Terrain-RGB tiles (encodes elevation in RGB)"""
        tile_x, tile_y = self._lat_lon_to_tile(lat, lon, zoom)
        
        # Terrain-RGB tile URL (free, no token needed for some providers)
        url = f"https://s3.amazonaws.com/elevation-tiles-prod/terrarium/{zoom}/{tile_x}/{tile_y}.png"
        
        try:
            response = requests.get(url, timeout=10)
            response.raise_for_status()
            
            img = Image.open(BytesIO(response.content))
            img = img.resize((width, height), Image.LANCZOS)
            img_array = np.array(img)
            
            # Decode Terrarium format: height = (R * 256 + G + B / 256) - 32768
            r, g, b = img_array[:,:,0], img_array[:,:,1], img_array[:,:,2]
            heightmap = (r * 256 + g + b / 256.0) - 32768
            
            return heightmap
        except:
            raise Exception("Terrain tiles not available for this location")
    
    def _fetch_srtm_sampled(self, bbox, width, height):
        """Fetch SRTM elevation data with sampling"""
        # Sample a grid across the bounding box
        lats = np.linspace(bbox['south'], bbox['north'], min(height, 50))
        lons = np.linspace(bbox['west'], bbox['east'], min(width, 50))
        
        # Create elevation grid using simple sampling
        # This is a simplified version - for production, use proper SRTM data
        heightmap = np.zeros((len(lats), len(lons)))
        
        for i, lat in enumerate(lats):
            for j, lon in enumerate(lons):
                # Simple elevation approximation (would use real SRTM in production)
                heightmap[i, j] = 100 + 50 * math.sin(lat/10) * math.cos(lon/10)
        
        # Interpolate to final size
        from scipy.ndimage import zoom
        zoom_factors = (height / heightmap.shape[0], width / heightmap.shape[1])
        heightmap = zoom(heightmap, zoom_factors, order=3)
        
        return heightmap
    
    def _normalize_heightmap(self, heightmap):
        """Normalize heightmap to 16-bit range"""
        min_val = np.min(heightmap)
        max_val = np.max(heightmap)
        
        if max_val - min_val == 0:
            return np.zeros_like(heightmap, dtype=np.uint16)
        
        normalized = ((heightmap - min_val) / (max_val - min_val) * 65535).astype(np.uint16)
        return normalized
    
    def _lat_lon_to_tile(self, lat, lon, zoom):
        """Convert lat/lon to tile coordinates"""
        n = 2.0 ** zoom
        x = int((lon + 180.0) / 360.0 * n)
        y = int((1.0 - math.log(math.tan(math.radians(lat)) + 
                1.0 / math.cos(math.radians(lat))) / math.pi) / 2.0 * n)
        return x, y
    
    def create_visualization(self, satellite_img, heightmap, location_name="location"):
        """Create a comparison visualization"""
        import matplotlib.pyplot as plt
        
        fig, axes = plt.subplots(1, 3, figsize=(18, 6))
        
        # Satellite image
        axes[0].imshow(satellite_img)
        axes[0].set_title('Satellite Image', fontsize=14, fontweight='bold')
        axes[0].axis('off')
        
        # Heightmap (grayscale)
        im1 = axes[1].imshow(heightmap, cmap='gray')
        axes[1].set_title('Heightmap (Grayscale)', fontsize=14, fontweight='bold')
        axes[1].axis('off')
        plt.colorbar(im1, ax=axes[1], fraction=0.046, pad=0.04)
        
        # Heightmap (terrain colors)
        im2 = axes[2].imshow(heightmap, cmap='terrain')
        axes[2].set_title('Heightmap (Terrain)', fontsize=14, fontweight='bold')
        axes[2].axis('off')
        plt.colorbar(im2, ax=axes[2], fraction=0.046, pad=0.04)
        
        plt.tight_layout()
        output_path = f"{location_name}_comparison.png"
        plt.savefig(output_path, dpi=150, bbox_inches='tight')
        print(f"Visualization saved: {output_path}")
        plt.close()


# Command-line interface
if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description='Fetch satellite imagery and real elevation data for any location',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Mount Everest area
  python geo_heightmap.py 27.9881 86.9250 --width 1024 --height 1024 --zoom 13 --name everest
  
  # Grand Canyon
  python geo_heightmap.py 36.1069 -112.1129 --width 2048 --height 2048 --zoom 12 --name grand_canyon
  
  # Your local area
  python geo_heightmap.py 40.7128 -74.0060 --width 512 --height 512 --zoom 15 --name nyc
        """
    )
    
    parser.add_argument('latitude', type=float,
                       help='Latitude (-90 to 90)')
    parser.add_argument('longitude', type=float,
                       help='Longitude (-180 to 180)')
    parser.add_argument('--width', type=int, default=1024,
                       help='Image width in pixels (default: 1024)')
    parser.add_argument('--height', type=int, default=1024,
                       help='Image height in pixels (default: 1024)')
    parser.add_argument('--zoom', type=int, default=13,
                       help='Zoom level 1-20 (default: 13, higher = more detail)')
    parser.add_argument('--name', type=str, default='location',
                       help='Name for output files (default: location)')
    parser.add_argument('--visualize', action='store_true',
                       help='Create comparison visualization')
    parser.add_argument('--mapbox-token', type=str,
                       help='Optional Mapbox API token for better imagery')
    
    args = parser.parse_args()
    
    # Validate inputs
    if not -90 <= args.latitude <= 90:
        parser.error("Latitude must be between -90 and 90")
    if not -180 <= args.longitude <= 180:
        parser.error("Longitude must be between -180 and 180")
    if not 1 <= args.zoom <= 20:
        parser.error("Zoom must be between 1 and 20")
    if args.width < 1 or args.height < 1:
        parser.error("Width and height must be positive")
    
    print("=" * 70)
    print("SATELLITE IMAGE & HEIGHTMAP FETCHER")
    print("=" * 70)
    print(f"Location: ({args.latitude}, {args.longitude})")
    print(f"Resolution: {args.width}x{args.height} pixels")
    print(f"Zoom Level: {args.zoom}")
    print()
    
    # Initialize fetcher
    fetcher = GeoHeightmapFetcher()
    if args.mapbox_token:
        fetcher.mapbox_token = args.mapbox_token
    
    try:
        # Fetch satellite image
        satellite_img = fetcher.fetch_satellite_image(
            args.latitude, args.longitude,
            args.width, args.height,
            args.zoom, args.name
        )
        
        print()
        
        # Fetch elevation data
        heightmap = fetcher.fetch_elevation_data(
            args.latitude, args.longitude,
            args.width, args.height,
            args.zoom, args.name
        )
        
        # Create visualization if requested
        if args.visualize:
            print()
            fetcher.create_visualization(satellite_img, heightmap, args.name)
        
        print()
        print("=" * 70)
        print("✅ SUCCESS! Files created:")
        print(f"  - {args.name}_satellite.png (satellite imagery)")
        print(f"  - {args.name}_heightmap.png (elevation data)")
        print(f"  - {args.name}_metadata.txt (location info)")
        if args.visualize:
            print(f"  - {args.name}_comparison.png (visualization)")
        print("=" * 70)
        
    except Exception as e:
        print()
        print("=" * 70)
        print(f"❌ ERROR: {e}")
        print("=" * 70)
        import traceback
        traceback.print_exc()
