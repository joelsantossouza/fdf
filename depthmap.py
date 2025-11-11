# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    depthmap.py                                        :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/11 23:04:23 by joesanto          #+#    #+#              #
#    Updated: 2025/11/11 23:24:42 by joesanto         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

"""
Advanced Image to Heightmap Converter
Converts photos to heightmaps using AI depth estimation and context understanding
"""

import cv2
import numpy as np
import torch
from PIL import Image
import matplotlib.pyplot as plt
from pathlib import Path

class HeightmapConverter:
    def __init__(self, use_gpu=True):
        """
        Initialize the heightmap converter with AI models
        
        Args:
            use_gpu: Use GPU acceleration if available
        """
        self.device = torch.device('cuda' if use_gpu and torch.cuda.is_available() else 'cpu')
        print(f"Using device: {self.device}")
        
        # Load MiDaS depth estimation model
        self.load_depth_model()
        
    def load_depth_model(self):
        """Load the MiDaS depth estimation model"""
        print("Loading depth estimation model...")
        
        # MiDaS v3.1 - Best balance of speed and accuracy
        self.depth_model = torch.hub.load("intel-isl/MiDaS", "DPT_Hybrid")
        self.depth_model.to(self.device)
        self.depth_model.eval()
        
        # Load transforms
        midas_transforms = torch.hub.load("intel-isl/MiDaS", "transforms")
        self.transform = midas_transforms.dpt_transform
        
        print("Model loaded successfully!")
    
    def estimate_depth(self, image):
        """
        Estimate depth map from image using AI
        
        Args:
            image: Input image (numpy array, BGR format)
            
        Returns:
            Depth map (numpy array)
        """
        # Convert BGR to RGB
        img_rgb = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
        
        # Prepare input
        input_batch = self.transform(img_rgb).to(self.device)
        
        # Predict depth
        with torch.no_grad():
            prediction = self.depth_model(input_batch)
            prediction = torch.nn.functional.interpolate(
                prediction.unsqueeze(1),
                size=img_rgb.shape[:2],
                mode="bicubic",
                align_corners=False,
            ).squeeze()
        
        depth_map = prediction.cpu().numpy()
        return depth_map
    
    def enhance_with_shading(self, image, depth_map, strength=0.3):
        """
        Enhance depth map using shading information from the original image
        
        Args:
            image: Original image
            depth_map: Initial depth map
            strength: How much to blend shading info (0-1)
            
        Returns:
            Enhanced depth map
        """
        # Convert to grayscale to analyze brightness
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        
        # Normalize grayscale
        gray_norm = gray.astype(float) / 255.0
        
        # Detect edges (high gradients = potential height changes)
        edges = cv2.Canny(gray, 50, 150)
        edges_norm = edges.astype(float) / 255.0
        
        # Apply bilateral filter to preserve edges while smoothing
        gray_smooth = cv2.bilateralFilter(gray_norm.astype(np.float32), 9, 75, 75)
        
        # Normalize depth map
        depth_norm = (depth_map - depth_map.min()) / (depth_map.max() - depth_map.min())
        
        # Blend depth with shading information
        # Where we have strong edges, trust the AI depth more
        edge_weight = 1 - edges_norm * 0.5
        shading_contribution = gray_smooth * strength * edge_weight
        
        enhanced_depth = depth_norm * (1 - strength) + shading_contribution
        
        return enhanced_depth
    
    def detect_lighting_direction(self, image):
        """
        Estimate the main lighting direction in the image
        This helps understand shadows correctly
        
        Args:
            image: Input image
            
        Returns:
            Lighting direction vector (approximate)
        """
        gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
        
        # Use Sobel operators to find gradient directions
        sobelx = cv2.Sobel(gray, cv2.CV_64F, 1, 0, ksize=5)
        sobely = cv2.Sobel(gray, cv2.CV_64F, 0, 1, ksize=5)
        
        # Dominant gradient direction indicates lighting
        avg_grad_x = np.mean(sobelx)
        avg_grad_y = np.mean(sobely)
        
        # Normalize
        magnitude = np.sqrt(avg_grad_x**2 + avg_grad_y**2)
        if magnitude > 0:
            light_dir = (avg_grad_x / magnitude, avg_grad_y / magnitude)
        else:
            light_dir = (0, -1)  # Default: top lighting
        
        return light_dir
    
    def apply_morphological_refinement(self, depth_map, iterations=2):
        """
        Refine depth map using morphological operations
        Helps smooth out artifacts while preserving features
        
        Args:
            depth_map: Input depth map
            iterations: Number of refinement iterations
            
        Returns:
            Refined depth map
        """
        # Normalize to 0-255 range for processing
        depth_8bit = ((depth_map - depth_map.min()) / 
                      (depth_map.max() - depth_map.min()) * 255).astype(np.uint8)
        
        # Apply opening (erosion followed by dilation) to remove noise
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))
        refined = cv2.morphologyEx(depth_8bit, cv2.MORPH_OPEN, kernel, iterations=iterations)
        
        # Apply closing (dilation followed by erosion) to fill gaps
        refined = cv2.morphologyEx(refined, cv2.MORPH_CLOSE, kernel, iterations=iterations)
        
        # Apply Gaussian blur for smoothness
        refined = cv2.GaussianBlur(refined, (5, 5), 0)
        
        # Convert back to float
        refined_float = refined.astype(float) / 255.0
        
        return refined_float
    
    def convert_to_heightmap(self, image_path, shading_strength=0.3, 
                           invert=False, enhance_contrast=True, 
                           smooth_iterations=2):
        """
        Main conversion function: Image -> Heightmap
        
        Args:
            image_path: Path to input image
            shading_strength: How much to use shading info (0-1)
            invert: Invert the heightmap (useful for craters/depressions)
            enhance_contrast: Enhance the contrast of the heightmap
            smooth_iterations: Number of smoothing iterations
            
        Returns:
            Heightmap as numpy array
        """
        print(f"Processing: {image_path}")
        
        # Load image
        image = cv2.imread(str(image_path))
        if image is None:
            raise ValueError(f"Could not load image: {image_path}")
        
        print("Step 1: Estimating depth using AI...")
        depth_map = self.estimate_depth(image)
        
        print("Step 2: Detecting lighting direction...")
        light_dir = self.detect_lighting_direction(image)
        print(f"  Estimated light direction: {light_dir}")
        
        print("Step 3: Enhancing with shading information...")
        enhanced_depth = self.enhance_with_shading(image, depth_map, shading_strength)
        
        print("Step 4: Refining with morphological operations...")
        refined_depth = self.apply_morphological_refinement(enhanced_depth, smooth_iterations)
        
        # Invert if requested (for surfaces like moon craters)
        if invert:
            print("Step 5: Inverting heightmap...")
            refined_depth = 1 - refined_depth
        
        # Enhance contrast if requested
        if enhance_contrast:
            print("Step 6: Enhancing contrast...")
            refined_depth = self.enhance_contrast(refined_depth)
        
        # Convert to 16-bit heightmap (standard format)
        heightmap = (refined_depth * 65535).astype(np.uint16)
        
        # Auto-generate output path: original_name_height.extension
        input_path = Path(image_path)
        output_path = input_path.parent / f"{input_path.stem}_height{input_path.suffix}"
        
        cv2.imwrite(str(output_path), heightmap)
        print(f"Heightmap saved to: {output_path}")
        
        return heightmap
    
    def enhance_contrast(self, depth_map, clip_percentile=2):
        """
        Enhance contrast using histogram stretching
        
        Args:
            depth_map: Input depth map
            clip_percentile: Percentage of extremes to clip
            
        Returns:
            Contrast-enhanced depth map
        """
        # Calculate percentiles for clipping
        low = np.percentile(depth_map, clip_percentile)
        high = np.percentile(depth_map, 100 - clip_percentile)
        
        # Clip and normalize
        clipped = np.clip(depth_map, low, high)
        enhanced = (clipped - low) / (high - low)
        
        # Apply mild gamma correction for better mid-tones
        gamma = 1.2
        enhanced = np.power(enhanced, gamma)
        
        return enhanced
    
    def visualize_results(self, image_path, heightmap):
        """
        Create a visualization comparing input and output
        
        Args:
            image_path: Path to original image
            heightmap: Generated heightmap
        """
        # Load original
        original = cv2.imread(str(image_path))
        original_rgb = cv2.cvtColor(original, cv2.COLOR_BGR2RGB)
        
        # Normalize heightmap for display
        heightmap_display = heightmap.astype(float) / 65535.0
        
        # Create figure with subplots
        fig, axes = plt.subplots(1, 3, figsize=(18, 6))
        
        # Original image
        axes[0].imshow(original_rgb)
        axes[0].set_title('Original Image', fontsize=14, fontweight='bold')
        axes[0].axis('off')
        
        # Heightmap (grayscale)
        im1 = axes[1].imshow(heightmap_display, cmap='gray')
        axes[1].set_title('Heightmap (Grayscale)', fontsize=14, fontweight='bold')
        axes[1].axis('off')
        plt.colorbar(im1, ax=axes[1], fraction=0.046, pad=0.04)
        
        # Heightmap (terrain colormap)
        im2 = axes[2].imshow(heightmap_display, cmap='terrain')
        axes[2].set_title('Heightmap (Terrain Colors)', fontsize=14, fontweight='bold')
        axes[2].axis('off')
        plt.colorbar(im2, ax=axes[2], fraction=0.046, pad=0.04)
        
        plt.tight_layout()
        plt.savefig('heightmap_comparison.png', dpi=150, bbox_inches='tight')
        plt.show()
        print("Visualization saved as 'heightmap_comparison.png'")


# Example usage
if __name__ == "__main__":
    import argparse
    
    # Set up command-line arguments
    parser = argparse.ArgumentParser(
        description='Convert images to heightmaps using AI depth estimation',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  python heightmap_converter.py moon.jpg --invert --shading 0.4
  python heightmap_converter.py mountain.jpg --contrast --smooth 3
  python heightmap_converter.py photo.jpg --shading 0.2 --no-contrast
        """
    )
    
    parser.add_argument('image', type=str, 
                       help='Input image path')
    parser.add_argument('--shading', type=float, default=0.3,
                       help='Shading strength (0.0-1.0, default: 0.3)')
    parser.add_argument('--invert', action='store_true',
                       help='Invert heightmap (use for craters/depressions)')
    parser.add_argument('--contrast', dest='enhance_contrast', action='store_true',
                       help='Enhance contrast (default)')
    parser.add_argument('--no-contrast', dest='enhance_contrast', action='store_false',
                       help='Disable contrast enhancement')
    parser.add_argument('--smooth', type=int, default=2,
                       help='Smoothing iterations (0-5, default: 2)')
    parser.add_argument('--no-gpu', action='store_true',
                       help='Disable GPU acceleration (use CPU only)')
    parser.add_argument('--visualize', action='store_true',
                       help='Generate comparison visualization')
    
    parser.set_defaults(enhance_contrast=True)
    
    args = parser.parse_args()
    
    # Validate arguments
    if not 0.0 <= args.shading <= 1.0:
        parser.error("--shading must be between 0.0 and 1.0")
    if not 0 <= args.smooth <= 5:
        parser.error("--smooth must be between 0 and 5")
    
    # Initialize converter
    print("=" * 60)
    print("IMAGE TO HEIGHTMAP CONVERTER")
    print("=" * 60)
    converter = HeightmapConverter(use_gpu=not args.no_gpu)
    
    # Convert with specified parameters
    print(f"\nSettings:")
    print(f"  Shading strength: {args.shading}")
    print(f"  Invert: {args.invert}")
    print(f"  Enhance contrast: {args.enhance_contrast}")
    print(f"  Smooth iterations: {args.smooth}")
    print()
    
    heightmap = converter.convert_to_heightmap(
        args.image,
        shading_strength=args.shading,
        invert=args.invert,
        enhance_contrast=args.enhance_contrast,
        smooth_iterations=args.smooth
    )
    
    # Generate visualization if requested
    if args.visualize:
        print("\nGenerating visualization...")
        converter.visualize_results(args.image, heightmap)
    
    print("\n" + "=" * 60)
    print("✅ CONVERSION COMPLETE!")
    print("=" * 60)
