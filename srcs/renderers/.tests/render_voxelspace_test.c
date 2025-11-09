/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 13:48:41 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "voxelspace.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define WIDTH	1500
#define HEIGHT	1000
#define SPEED	1
#define PI		3.14159265359

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
t_camera	camera;
double angle = 0;

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
	else if (keycode == KEY3)
	{
		angle += 0.1;
		camera.angle.cos = cos(angle);
		camera.angle.sin = sin(angle);
	}
	else if (keycode == KEY4)
	{
		angle -= 0.1;
		camera.angle.cos = cos(angle);
		camera.angle.sin = sin(angle);
	}
	else if (keycode == KEY5)
		camera.horizon -= SPEED * 3;
	else if (keycode == KEY6)
		camera.horizon += SPEED * 3;
	render_voxelspace(&image, &map, &camera);
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
		if (parse_voxel_file(argv[1], argv[2], &map) < 0)
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
	camera = (t_camera){
		.position.x = map.width / 2,
		.position.y = map.height / 2,
		.angle.cos = cos(0),
		.angle.sin = sin(0),
		.horizon = image.height / 2,
		.zfar = 250,
		.altitude = 150,
		.scale = 200,
	};
	mlx_hook(window, 2, 1L<<0, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
