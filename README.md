# 🗻 FdF - Fil de Fer

A high-performance 3D wireframe renderer with isometric projection and voxelspace rendering capabilities.

<img width="1400" height="1009" alt="Image" src="https://github.com/user-attachments/assets/53017486-18d8-4c0f-bcbf-72dd2d7eb26f" />

## 🌟 Overview

**FdF** (Fil de Fer - French for "wireframe") is a graphics project that renders 3D wireframe models in isometric projection. This project explores fundamental computer graphics concepts including:

- Vector mathematics and transformations
- Matrix multiplication
- Line drawing algorithms (Bresenham, Xiaolin Wu)
- Performance optimization techniques

Built with **MinilibX**, a lightweight graphics library for creating efficient visual applications.

## 🎯 Key Features

- ✨ Real-time 3D wireframe rendering
- 🎨 Custom color mapping with hexadecimal values
- 🔄 Interactive rotation on all three axes
- 🔍 Dynamic zoom and altitude scaling
- 🎮 **BONUS:** First-person voxelspace exploration
- 🖼️ **BONUS:** Image import
- 🌅 **BONUS:** Custom skybox rendering

## 🚀 Getting Started

### Dependencies

Install MinilibX dependencies:

```bash
sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev
```

### Building

```bash
make
```

This generates the `fdf` executable.

### Basic Usage

**Load a wireframe map:**
```bash
./fdf <map.fdf>
```

**Load from images (BONUS):**
```bash
./fdf --images <color_image> <height_image>
```

**Load with custom skybox (BONUS):**
```bash
./fdf --images <color_image> <height_image> --sky <sky_image>
```

> **Note:** For image import, both color and height images must have identical dimensions. High-resolution images recommended for skybox feature.

## 📝 Map Format

### Standard `.fdf` Format

Create custom heightmaps using space-separated altitude values:

```
0  0  0  0  0  0  0  0  0
0  0 10 10  0  0 10 10  0
0  0 10 10  0  0 10 10  0
0  0 10 10 10 10 10 10  0
0  0  0 10 10 10 10 10  0
0  0  0  0  0  0 10 10  0
0  0  0  0  0  0  0  0  0
```

**Requirements:**
- All rows must have the same number of points
- Values represent point altitude/elevation

### Custom Colors

Add hexadecimal colors after altitude values:

```
0,0x0000FF 0,0x0000FF 1,0x0080FF 2,0x00FFFF 3,0x00FF80
0,0x0000FF 0,0x0000FF 0,0x0000FF 1,0x0080FF 2,0x00FFFF
0,0x0000FF 0,0x0000FF 0,0x0000FF 0,0x0000FF 1,0x0080FF
```

Format: `altitude,0xRRGGBB`

### Image-Based Maps (BONUS)

Import any image

<img width="1155" height="850" alt="Image" src="https://github.com/user-attachments/assets/c7d72d22-499b-45a8-95e6-96be651a5675" />

- **Color image:** Determines map texture/appearance
- **Height image:** Brightness = elevation (white = high, black = low)

> **Tip:** Use grayscale heightmaps for best results.

## ⌨️ Controls

### Wireframe Mode

**Movement:**
- `W` - Move up
- `A` - Move left
- `S` - Move down
- `D` - Move right

**Rotation:**
- `J` / `K` - Rotate around X-axis (down/up)
- `H` / `L` - Rotate around Y-axis (left/right)
- `U` / `I` - Rotate around Z-axis (left/right)

**Zoom:**
- `SHIFT` - Zoom in
- `CTRL` - Zoom out

**Other:**
- `SPACE` - Toggle line algorithm (Bresenham ↔ Xiaolin Wu)
- `O` - Switch to 2D view
- `Q` / `E` - Scale altitude down/up
- `TAB` - **Enter voxelspace mode** 🎮

### Voxelspace Mode (BONUS)

**Movement:**
- `W` - Move forward
- `A` - Move left
- `S` - Move backward
- `D` - Move right
- `SPACE` - Jump (fly up)
- `CTRL` - Dive (fly down)
- `SHIFT` - Run (sprint)
- `DOUBLE SPACE` - Toggle fly/walk mode

**Camera:**
- `MOUSE` - Free-look rotation

**Other:**
- `Q` / `E` - Scale voxel altitude down/up
- `TAB` - Return to wireframe mode

> **Note:** If your mouse look weird, uncomment the indicated line on ./srcs/main.c
<img width="1382" height="462" alt="Image" src="https://github.com/user-attachments/assets/1729280b-e957-4253-ad65-7ca01dbe2e73" />

## 🎨 Voxelspace Rendering

The bonus voxelspace renderer provides a first-person exploration experience using ray-marching techniques:

<img width="1917" height="1011" alt="Image" src="https://github.com/user-attachments/assets/4c64980c-7700-49c5-880b-ed72ccacbf4d" />

### How It Works

1. **Ray Calculation:** Compute angles for all rays within the player's field of view
2. **Ray Marching:** Traverse each ray point-by-point to sample voxel heights
3. **Occlusion Culling:** Track the highest visible voxel per column
4. **Smart Rendering:** Only draw voxels higher than previously seen heights

This technique efficiently renders terrain by automatically hiding occluded voxels behind taller ones.

## 🖼️ Example Usage

```bash
# Basic wireframe rendering
./fdf maps/fdf/42.fdf

# Import custom images
./fdf --images maps/voxel/volcano/volcano.png maps/voxel/volcano/volcano_height.png

# Full experience with skybox
./fdf --images maps/voxel/volcano/volcano.png maps/voxel/volcano/volcano_height.png --sky maps/sky/black_hole.png
```

*Transforming data into immersive 3D worlds.*

<img width="1917" height="1011" alt="Image" src="https://github.com/user-attachments/assets/b1f4ae60-ff1f-4447-9298-2d222c4b9e22" />
