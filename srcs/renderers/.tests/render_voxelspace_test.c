/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/07 15:11:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define WIDTH	1000
#define HEIGHT	1000
#define SPEED	1

# define KEY1 65436
# define KEY2 65433
# define KEY3 65435
# define KEY4 65430
# define KEY5 65437
# define KEY6 65432
# define KEY7 65429
# define KEY8 65431

void	*mlx;
void	*window;
t_image	image;
t_map	map;
t_voxelspace	vox;
t_camera	camera;

#include <gif_lib.h>
#include <stdlib.h>

#define ERROR -1
#define SUCCESS 0
#define WHITE 0xFFFFFF

static void	free_map(t_map *map, void *unused)
{
	(void)unused;
	if (map->altitude)
		free(map->altitude);
	if (map->color)
		free(map->color);
	map->altitude = NULL;
	map->color = NULL;
	map->width = 0;
	map->height = 0;
	map->total = 0;
}

static int	extract_altitude_from_pixel(int pixel)
{
	int	r;
	int	g;
	int	b;
	int	grayscale;

	// Extract RGB from packed pixel (0xRRGGBBAA)
	r = (pixel >> 24) & 0xFF;
	g = (pixel >> 16) & 0xFF;
	b = (pixel >> 8) & 0xFF;
	// Convert to grayscale using standard weights
	grayscale = (r * 299 + g * 587 + b * 114) / 1000;
	// Map 0-255 to altitude range (e.g., 0-255 or scale as needed)
	return (grayscale);
}

static int	extract_color_from_pixel(int pixel)
{
	int	r;
	int	g;
	int	b;

	// Extract RGB from packed pixel (0xRRGGBBAA)
	r = (pixel >> 24) & 0xFF;
	g = (pixel >> 16) & 0xFF;
	b = (pixel >> 8) & 0xFF;
	// Return as 0xRRGGBB format
	return ((r << 16) | (g << 8) | b);
}

static int	*read_gif_pixels(const char *path, int *width, int *height)
{
	GifFileType		*gif_file;
	SavedImage		*image;
	ColorMapObject	*color_map;
	GifByteType		*raster;
	int				*pixels;
	int				i;
	int				error;

	gif_file = DGifOpenFileName(path, &error);
	if (!gif_file)
		return (NULL);
	if (DGifSlurp(gif_file) == GIF_ERROR)
		return (DGifCloseFile(gif_file, &error), NULL);
	*width = gif_file->SWidth;
	*height = gif_file->SHeight;
	pixels = malloc(sizeof(*pixels) * (*width) * (*height));
	if (!pixels)
		return (DGifCloseFile(gif_file, &error), NULL);
	image = &gif_file->SavedImages[0];
	raster = image->RasterBits;
	color_map = image->ImageDesc.ColorMap ? 
				image->ImageDesc.ColorMap : gif_file->SColorMap;
	if (!color_map)
		return (free(pixels), DGifCloseFile(gif_file, &error), NULL);
	i = -1;
	while (++i < (*width) * (*height))
	{
		if (raster[i] < color_map->ColorCount)
		{
			GifColorType color = color_map->Colors[raster[i]];
			pixels[i] = (color.Red << 24) | (color.Green << 16) | 
						(color.Blue << 8) | 0xFF;
		}
		else
			pixels[i] = 0x000000FF;
	}
	DGifCloseFile(gif_file, &error);
	return (pixels);
}

static int	validate_gif_map(const char *height_path, const char *color_path, t_map *map)
{
	int	*height_pixels;
	int	*color_pixels;
	int	color_width;
	int	color_height;

	height_pixels = read_gif_pixels(height_path, &map->width, &map->height);
	if (!height_pixels)
		return (ERROR);
	if (!map->width || !map->height)
		return (free(height_pixels), ERROR);
	map->total = map->width * map->height;
	color_pixels = read_gif_pixels(color_path, &color_width, &color_height);
	if (!color_pixels)
		return (free(height_pixels), ERROR);
	if (color_width != map->width || color_height != map->height)
		return (free(height_pixels), free(color_pixels), ERROR);
	map->altitude = malloc(sizeof(*map->altitude) * map->total);
	map->color = malloc(sizeof(*map->color) * map->total);
	if (!map->altitude || !map->color)
		return (free(height_pixels), free(color_pixels), free_map(map, NULL), ERROR);
	return (SUCCESS);
}

int	parse_gif_file(const char *height_path, const char *color_path, t_map *map)
{
	int	*height_pixels;
	int	*color_pixels;
	int	i;
	int	width;
	int	height;

	ft_bzero(map, sizeof(*map));
	if (validate_gif_map(height_path, color_path, map) < 0)
		return (free_map(map, NULL), ERROR);
	height_pixels = read_gif_pixels(height_path, &width, &height);
	color_pixels = read_gif_pixels(color_path, &width, &height);
	if (!height_pixels || !color_pixels)
		return (free(height_pixels), free(color_pixels), free_map(map, NULL), ERROR);
	i = -1;
	while (++i < map->total)
	{
		map->altitude[i] = extract_altitude_from_pixel(height_pixels[i]);
		map->color[i] = extract_color_from_pixel(color_pixels[i]);
	}
	free(height_pixels);
	free(color_pixels);
	return (SUCCESS);
}

// Example usage:
/*
int main(int argc, char **argv)
{
	t_map	map;

	if (argc != 3)
		return (write(2, "Usage: ./program height.gif color.gif\n", 39), 1);
	if (parse_gif_file(argv[1], argv[2], &map) < 0)
		return (write(2, "Error loading GIF files\n", 24), 1);
	
	printf("Map Info:\n");
	printf("Width: %d\n", map.width);
	printf("Height: %d\n", map.height);
	printf("Total: %d\n", map.total);
	printf("First altitude: %ld\n", map.altitude[0]);
	printf("First color: 0x%06X\n", map.color[0]);
	
	free_map(&map, NULL);
	return (0);
}
*/

int	render(int keycode)
{
	ft_bzero(image.addr, WIDTH * HEIGHT * (image.bpp / 8));
	if (keycode == 119)
		camera.position.y -= SPEED;
	else if (keycode == 97)
		camera.position.x -= SPEED;
	else if (keycode == 115)
		camera.position.y += SPEED;
	else if (keycode == 100)
		camera.position.x += SPEED;
	else if (keycode == KEY1)
		camera.altitude += SPEED;
	else if (keycode == KEY2)
		camera.altitude -= SPEED;
	render_voxelspace(&image, &vox, &camera);
	mlx_put_image_to_window(mlx, window, image.data, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int	temp;
	if (argc != 2)
	{
		ft_fprintf(2, "Usage: %s <map>\n", *argv);
		return (2);
	}
	mlx = mlx_init();
	if (!mlx)
		return (1);
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "Bresenham test");
	if (!window)
		return (2);
	image.data = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image.data)
		return (3);
	image.width = WIDTH;
	image.height = HEIGHT;
	image.addr = mlx_get_data_addr(image.data, &image.bpp, &image.linelen, &temp);
	if (parse_fdf_file(argv[1], &map) < 0)
	{
		ft_fprintf(2, "Fail to load map\n");
		return (1);
	}
	vox = (t_voxelspace) {
		.map = &map,
		.scale = 50,
	};
	camera = (t_camera){
		.position.x = map.width / 2,
		.position.y = map.height / 2,
		.zfar = 30,
		.altitude = 50,
	};
	mlx_hook(window, 2, 1L<<0, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
