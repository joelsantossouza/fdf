/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/07 21:18:44 by joesanto         ###   ########.fr       */
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
		fdf.angle.x += 0.1;
		fdf.trig.cosine.x = cos(fdf.angle.x);
		fdf.trig.sine.x = sin(fdf.angle.x);
	}
	else if (keycode == KEY2)
	{
		fdf.angle.x -= 0.1;
		fdf.trig.cosine.x = cos(fdf.angle.x);
		fdf.trig.sine.x = sin(fdf.angle.x);
	}
	else if (keycode == KEY3)
	{
		fdf.angle.y += 0.1;
		fdf.trig.cosine.y = cos(fdf.angle.y);
		fdf.trig.sine.y = sin(fdf.angle.y);
	}
	else if (keycode == KEY4)
	{
		fdf.angle.y -= 0.1;
		fdf.trig.cosine.y = cos(fdf.angle.y);
		fdf.trig.sine.y = sin(fdf.angle.y);
	}
	else if (keycode == KEY5)
	{
		fdf.angle.z += 0.1;
		fdf.trig.cosine.z = cos(fdf.angle.z);
		fdf.trig.sine.z = sin(fdf.angle.z);
	}
	else if (keycode == KEY6)
	{
		fdf.angle.z -= 0.1;
		fdf.trig.cosine.z = cos(fdf.angle.z);
		fdf.trig.sine.z = sin(fdf.angle.z);
	}
	else if (keycode == KEY7)
		fdf.spacing -= 1;
	else if (keycode == KEY8)
		fdf.spacing += 1;
//	else if (keycode == KEY7)
//		fdf.zoom /= 1.1;
//	else if (keycode == KEY8)
//		fdf.zoom *= 1.1;
	render_fdf(&image, &fdf, drawline);
	mlx_put_image_to_window(mlx, window, image.data, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int	temp;
	if (argc != 3)
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
	if (parse_voxel_file(argv[1], argv[2], &map) < 0)
	{
		ft_fprintf(2, "Fail to load map\n");
		return (1);
	}
	fdf = (t_fdf) {
		.map = &map,
		.center.x = -(map.width / 2 * 15),
		.center.y = -(map.height / 2 * 15),
		.position.x = WIDTH / 2,
		.position.y = HEIGHT / 2,
		.spacing = 15,
		//.zoom = 1,
	};
	fdf.trig.cosine.x = cos(fdf.angle.x);
	fdf.trig.sine.x = sin(fdf.angle.x);
	fdf.trig.cosine.y = cos(fdf.angle.y);
	fdf.trig.sine.y = sin(fdf.angle.y);
	fdf.trig.cosine.z = cos(fdf.angle.z);
	fdf.trig.sine.z = sin(fdf.angle.z);
	fdf.transformed = malloc(sizeof(t_point) * fdf.map->total);
	if (!fdf.transformed)
		return (3);
	mlx_hook(window, 2, 1L<<0, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
