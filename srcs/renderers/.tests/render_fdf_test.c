/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/11 10:52:32 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include "voxelspace.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define WIDTH	1000
#define HEIGHT	1000
#define SPEED	10

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
t_fdf	fdf;
double anglex = 0;
double angley = 0;
double anglez = 0;

t_linedrawer *drawline = bresenham_drawline;

int	render(int keycode)
{
	ft_bzero(image.addr, WIDTH * HEIGHT * (image.bpp / 8));
	if (keycode == 113)
		drawline = bresenham_drawline;
	else if (keycode == 101)
		drawline = xiaolinwu_drawline;
	else if (keycode == 119)
		fdf.position.y -= SPEED;
	else if (keycode == 97)
		fdf.position.x -= SPEED;
	else if (keycode == 115)
		fdf.position.y += SPEED;
	else if (keycode == 100)
		fdf.position.x += SPEED;
	else if (keycode == KEY1)
	{
		anglex += 0.1;
		fdf.axis.x.cos = cos(anglex);
		fdf.axis.x.sin = sin(anglex);
	}
	else if (keycode == KEY2)
	{
		anglex -= 0.1;
		fdf.axis.x.cos = cos(anglex);
		fdf.axis.x.sin = sin(anglex);
	}
	else if (keycode == KEY3)
	{
		angley -= 0.1;
		fdf.axis.y.cos = cos(angley);
		fdf.axis.y.sin = sin(angley);
	}
	else if (keycode == KEY4)
	{
		angley += 0.1;
		fdf.axis.y.cos = cos(angley);
		fdf.axis.y.sin = sin(angley);
	}
	else if (keycode == KEY5)
	{
		anglez -= 0.1;
		fdf.axis.z.cos = cos(anglez);
		fdf.axis.z.sin = sin(anglez);
	}
	else if (keycode == KEY6)
	{
		anglez += 0.1;
		fdf.axis.z.cos = cos(anglez);
		fdf.axis.z.sin = sin(anglez);
	}
	else if (keycode == KEY7)
		fdf.zoom /= 1.1;
	else if (keycode == KEY8)
		fdf.zoom *= 1.1;
	render_fdf(&image, &fdf, drawline);
	mlx_put_image_to_window(mlx, window, image.data, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int	temp;
	if (argc == 2)
	{
		if (parse_fdf_file(argv[1], &map) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
	}
	else if (argc == 3)
	{
		if (parse_voxel_file(argv[1], argv[2], &map, 200) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
	}
	else
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
	fdf = (t_fdf) {
		.map = &map,
		.center.x = -(map.width / 2 * 15),
		.center.y = -(map.height / 2 * 15),
		.position.x = WIDTH / 2,
		.position.y = HEIGHT / 2,
		.spacing = 15,
		.zoom = 1,
	};
	fdf.axis.x.cos = cos(0);
	fdf.axis.x.sin = sin(0);
	fdf.axis.y.cos = cos(0);
	fdf.axis.y.sin = sin(0);
	fdf.axis.z.cos = cos(0);
	fdf.axis.z.sin = sin(0);
	fdf.transformed = malloc(sizeof(t_point) * map.total);
	if (!fdf.transformed)
		return (3);
	mlx_hook(window, 2, 1L<<0, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
