/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/11 23:00:42 by joesanto         ###   ########.fr       */
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
#define SPEED_JUMP 3 * 1000
#define SPEED	1
#define SENSIBILITY	0.05
#define PI		3.14159265359
#define PLAYER_HEIGHT 20 * 200
#define MAX_HEIGHT_TO_WALK PLAYER_HEIGHT

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
int	last_ph = PLAYER_HEIGHT / 2;
int	player_height = PLAYER_HEIGHT;
double	old_speed = SPEED / 3.0;
double speed = SPEED;
double force = 0;
int	up = 0;
int down = 0;
int left = 0;
int right = 0;
int direita = 0;
int esquerda = 0;
int jump = 0;
t_player player;
int run;

int	get_keys(int keycode)
{
	if (up)
	{
		t_trig ang = {sin(angle), cos(angle)};
		move_player(&player, &ang, &map);
	}
	if (direita)
	{
		t_trig ang = {sin(angle + PI / 2), cos(angle + PI / 2)};
		move_player(&player, &ang, &map);
	}
	if (esquerda)
	{
		t_trig ang = {sin(angle - PI / 2), cos(angle - PI / 2)};
		move_player(&player, &ang, &map);
	}
	if (down)
	{
		t_trig ang = {-sin(angle), -cos(angle)};
		move_player(&player, &ang, &map);
	}
	int height = map.altitude[map.width * (int)camera.position.y + (int)camera.position.x] + player_height;
	if (jump && camera.position.z == height)
		player.zforce = SPEED_JUMP;
	else if (keycode == KEY2)
	{
		int	tmp = player_height;
		player_height = last_ph;
		last_ph = tmp;
		double tmp1 = speed;
		speed = old_speed;
		old_speed = tmp1;
		camera.position.z -= last_ph - player_height;
	}
	if (run)
		player.speed = speed * 2;
	else
		player.speed = speed;
	if (right)
	{
		angle += SENSIBILITY;
		t_trig ang = {sin(angle), cos(angle)};
		camera.fov.plx = ang.cos * camera.zfar + ang.sin * camera.zfar;
		camera.fov.ply = ang.sin * camera.zfar - ang.cos * camera.zfar;
		camera.fov.prx = ang.cos * camera.zfar - ang.sin * camera.zfar;
		camera.fov.pry = ang.sin * camera.zfar + ang.cos * camera.zfar;
	}
	if (left)
	{
		angle -= SENSIBILITY;
		t_trig ang = {sin(angle), cos(angle)};
		camera.fov.plx = ang.cos * camera.zfar + ang.sin * camera.zfar;
		camera.fov.ply = ang.sin * camera.zfar - ang.cos * camera.zfar;
		camera.fov.prx = ang.cos * camera.zfar - ang.sin * camera.zfar;
		camera.fov.pry = ang.sin * camera.zfar + ang.cos * camera.zfar;
	}
	else if (keycode == KEY5)
		camera.horizon -= speed * 100;
	else if (keycode == KEY6)
		camera.horizon += speed * 100;
	return (0);
}

int press(int keycode)
{
	if (keycode == 119)
		up = 1;
	else if (keycode == 115)
		down = 1;
	else if (keycode == KEY6)
		direita = 1;
	else if (keycode == KEY4)
		esquerda = 1;
	else if (keycode == KEY1)
		jump = 1;
	else if (keycode == 100)
		right = 1;
	else if (keycode == 97)
		left = 1;
	else if (keycode == 65505)
		run = 1;
	return (0);
}

int release(int keycode)
{
	if (keycode == 119)
		up = 0;
	else if (keycode == 115)
		down = 0;
	else if (keycode == KEY6)
		direita = 0;
	else if (keycode == KEY4)
		esquerda = 0;
	else if (keycode == KEY1)
		jump = 0;
	else if (keycode == 100)
		right = 0;
	else if (keycode == 97)
		left = 0;
	else if (keycode == 65505)
		run = 0;
	return (0);
}


int	render()
{
	get_keys(0);
	gravity(&camera.position.z, &player.zforce, map.altitude[map.width * (int)camera.position.y + (int)camera.position.x] + player_height);
	printf("Force: %f\n", force);
	ft_bzero(image.addr, WIDTH * HEIGHT * (image.bpp / 8));
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
		if (parse_voxel_file(argv[1], argv[2], &map, 800) < 0)
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
		.position.x = map.width / 2.0,
		.position.y = map.height / 5.0,
		.position.z = 300 * 200,
		.horizon = image.height / 2,
		.zfar = 400,
	};
	t_trig ang = {sin(angle), cos(angle)};
	player = (t_player){&camera.position, player_height, speed, 0, MAX_HEIGHT_TO_WALK};
	camera.fov.plx = ang.cos * camera.zfar + ang.sin * camera.zfar;
	camera.fov.ply = ang.sin * camera.zfar - ang.cos * camera.zfar;
	camera.fov.prx = ang.cos * camera.zfar - ang.sin * camera.zfar;
	camera.fov.pry = ang.sin * camera.zfar + ang.cos * camera.zfar;
	mlx_hook(window, 2, 1L<<0, press, 0);
	mlx_hook(window, 3, 1L<<1, release, 0);
	mlx_loop_hook(mlx, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
