/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace_test.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/10 10:58:22 by joesanto         ###   ########.fr       */
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
#define SPEED	5
#define PI		3.14159265359
#define GRAVITY	1.10
#define MAX_HEIGHT_TO_WALK 10

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
int	player_height = 20;
double speed = 1;

int	render(int keycode)
{
	ft_bzero(image.addr, WIDTH * HEIGHT * (image.bpp / 8));
	if (keycode == 119)
	{
		t_trig	ang = {sin(angle), cos(angle)};
		int heightonmap = map.altitude[map.width * (int)(camera.position.y + ang.sin *SPEED) + (int)(camera.position.x + ang.cos * SPEED)];
		int	myheight = map.altitude[map.width * camera.position.y + camera.position.x];
		if (heightonmap - myheight <= MAX_HEIGHT_TO_WALK)
		{
			camera.altitude = heightonmap + player_height;
			camera.position.x += ang.cos * SPEED;
			camera.position.y += ang.sin * SPEED;
		}
	}
	else if (keycode == 115)
	{
		t_trig	ang = {sin(angle), cos(angle)};
		int heightonmap = map.altitude[map.width * (int)(camera.position.y - ang.sin *SPEED) + (int)(camera.position.x - ang.cos * SPEED)];
		int	myheight = map.altitude[map.width * camera.position.y + camera.position.x];
		if (heightonmap - myheight <= MAX_HEIGHT_TO_WALK)
		{
			camera.altitude = heightonmap + player_height;
			camera.position.x -= ang.cos * SPEED;
			camera.position.y -= ang.sin * SPEED;
		}
	}
	else if (keycode == KEY1)
		camera.altitude += SPEED;
	else if (keycode == KEY2)
		camera.altitude -= SPEED;
	else if (keycode == 100)
	{
		angle += 0.1;
		t_trig ang = {sin(angle), cos(angle)};
		camera.fov.plx = ang.cos * camera.zfar + ang.sin * camera.zfar;
		camera.fov.ply = ang.sin * camera.zfar - ang.cos * camera.zfar;
		camera.fov.prx = ang.cos * camera.zfar - ang.sin * camera.zfar;
		camera.fov.pry = ang.sin * camera.zfar + ang.cos * camera.zfar;
	}
	else if (keycode == 97)
	{
		angle -= 0.1;
		t_trig ang = {sin(angle), cos(angle)};
		camera.fov.plx = ang.cos * camera.zfar + ang.sin * camera.zfar;
		camera.fov.ply = ang.sin * camera.zfar - ang.cos * camera.zfar;
		camera.fov.prx = ang.cos * camera.zfar - ang.sin * camera.zfar;
		camera.fov.pry = ang.sin * camera.zfar + ang.cos * camera.zfar;
	}
	else if (keycode == KEY5)
		camera.horizon -= SPEED * 3;
	else if (keycode == KEY6)
		camera.horizon += SPEED * 3;
	int	heightonmap = map.altitude[map.width * camera.position.y + camera.position.x] + player_height;
	if (camera.altitude >  heightonmap)
	{
		speed *= GRAVITY;
		if (camera.altitude - speed < heightonmap)
		{
			camera.altitude = heightonmap;
			speed = 1;
		}
		else
			camera.altitude -= speed;
	}
	else
		speed = 1;
	printf("%f\n", speed);
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
		.position.y = map.height / 5,
		.horizon = image.height / 2,
		.zfar = 300,
		.altitude = 300,
		.scale = 300,
	};
	t_trig ang = {sin(angle), cos(angle)};
	camera.fov.plx = ang.cos * camera.zfar + ang.sin * camera.zfar;
	camera.fov.ply = ang.sin * camera.zfar - ang.cos * camera.zfar;
	camera.fov.prx = ang.cos * camera.zfar - ang.sin * camera.zfar;
	camera.fov.pry = ang.sin * camera.zfar + ang.cos * camera.zfar;
	mlx_hook(window, 2, 1L<<0, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
