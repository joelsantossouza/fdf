/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 18:34:30 by joesanto         ###   ########.fr       */
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
#define SENSIBILITY	0.03
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

int	main(int argc, char **argv)
{
	int	temp;
	t_map	map;
	void	*mlx;
	void	*window;
	t_image	image;
	t_camera	camera;
	t_player	player;
	t_physic world = {3, 1000, -HEIGHT + (HEIGHT / 1.5), HEIGHT + (HEIGHT >>1)};
	t_pic sky;

	if (argc == 3)
	{
		if (parse_fdf_file(argv[1], &map) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
		if (parse_picture(argv[2], &sky.data, &sky.width, &sky.height) < 0)
		{
			ft_fprintf(2, "Fail to load sky\n");
			return (1);
		}
	}
	else if (argc == 4)
	{
		if (parse_voxel_file(argv[1], argv[2], &map, world.unity) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
		if (parse_picture(argv[3], &sky.data, &sky.width, &sky.height) < 0)
		{
			ft_fprintf(2, "Fail to load sky\n");
			return (1);
		}
	}
	else
	{
		ft_fprintf(2, "Usage: %s <map> <sky>\n", *argv);
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
	image.center = (t_point){WIDTH >> 1, HEIGHT >> 1};
	image.addr = mlx_get_data_addr(image.data, &image.bpp, &image.linelen, &temp);
	image.bpp = image.bpp >> 3;
	camera = (t_camera){
		.pos.x = map.width / 2.0,
		.pos.y = map.height / 5.0,
		.pos.z = 300 * 200,
		.horizon = image.height >> 1,
		.zfar = 11000,
	};
	t_player_stats	stats = {
		.climb_max = 10 * 200,
		.sensibility = 0.001,
		.height = 80 * 200,
		.jump_force = 15 * 200,
		.dive_force = 2 * 200,
		.speed_max = 5,
		.run_speed_max = 9,
	};
	player = (t_player){
		.pos = &camera.pos,
		.cam = &camera,
		.speed = 1,
		.move = player_walk,
		.stats = &stats,
	};
	player.floor = map.altitude[map.width * (int)player.pos->y + (int)player.pos->x] + player.stats->height;
	t_vox vox = {
		.mlx = mlx,
		.window = window,
		.img = &image,
		.player = &player,
		.map = &map,
		.keyboard = 0,
		.world = &world,
		.sky = &sky,
	};
	vox.sky = 0;
	rotate_player(&player, 0);
	mlx_mouse_hide(mlx, window);
	mlx_hook(window, 2, 1L<<0, press_key, &vox.keyboard);
	mlx_hook(window, 3, 1L<<1, release_key, &vox.keyboard);
	mlx_hook(window, 6, 1L<<6, player_mouse, &vox);
	mlx_loop_hook(mlx, voxelspace_loop, &vox);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
