/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 17:51:00 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include "../../events/events.h"
#include "../../parsers/parsers.h"
#include "voxelspace.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define WIDTH	1920
#define HEIGHT	1080
#define SPEED	10

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
	t_app app;

	(void)argc;
	if (!(parse_arguments(argv, &app.map, &app.vox.sky, 0) & MAP_DONE))
	{
		ft_fprintf(2, "Fail to parse arguments\n");
		return (1);
	}
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.window = mlx_new_window(app.mlx, WIDTH, HEIGHT, "Bresenham test");
	if (!app.window)
		return (2);
	app.img.data = mlx_new_image(app.mlx, WIDTH, HEIGHT);
	if (!app.img.data)
		return (3);
	app.img.width = WIDTH;
	app.img.height = HEIGHT;
	app.img.addr = mlx_get_data_addr(app.img.data, &app.img.bpp, &app.img.linelen, &temp);
	app.img.bpp >>= 3;
	app.img.center = (t_point){WIDTH >>1, HEIGHT >>1};
	app.fdf.scale = 1;
	app.fdf.center.x = -(app.map.width / 2 * 15);
	app.fdf.center.y = -(app.map.height / 2 * 15);
	app.fdf.pos.x = WIDTH / 2;
	app.fdf.pos.y = HEIGHT / 2;
	app.fdf.spacing = 15;
	app.fdf.zoom = 1;
	double map_diag = sqrt(app.map.width * app.map.width + app.map.height + app.map.height);
	double screen_diag = sqrt(app.img.width * app.img.width + app.img.height * app.img.height);
	app.fdf.min_zoom = 0.02;
	app.fdf.max_zoom = screen_diag / (map_diag  *  0.5);
	app.fdf.drawline = bresenham_drawline;
	app.fdf.axis.angle_x = 0;
	app.fdf.axis.angle_y = 0;
	app.fdf.axis.angle_z = 0;
	app.fdf.axis.x.cos = cos(0);
	app.fdf.axis.x.sin = sin(0);
	app.fdf.axis.y.cos = cos(0);
	app.fdf.axis.y.sin = sin(0);
	app.fdf.axis.z.cos = cos(0);
	app.fdf.axis.z.sin = sin(0);
	app.fdf.transformed = malloc(sizeof(t_point) * app.map.total);
	if (!app.fdf.transformed)
		return (3);
	t_camera camera = (t_camera){
		.pos.x = app.map.width / 2.0,
		.pos.y = app.map.height / 5.0,
		.pos.z = 300,
		.horizon = app.img.height >> 1,
		.zfar = 1000,
		.scale = 200,
	};
	t_player_stats	stats = {
		.climb_max = 10,
		.sensibility = 0.001,
		.height = 10,
		.jump_force = 5,
		.dive_force = 5,
		.speed_max = 3,
		.run_speed_max = 7,
	};
	app.vox.player = (t_player){
		.pos = &camera.pos,
		.cam = &camera,
		.speed = 1,
		.move = player_walk,
		.stats = &stats,
	};
	t_player player = app.vox.player;
	app.vox.player.floor = app.map.altitude[app.map.width * (int)player.pos->y + (int)player.pos->x] + player.stats->height;
	app.vox.gravity = 0.0096;
	app.vox.min_horizon = -HEIGHT + (HEIGHT / 1.5);
	app.vox.max_horizon = HEIGHT + (HEIGHT >>1);
	app.keyboard = 0;
	rotate_player(&player, 0);
	mlx_mouse_hide(app.mlx, app.window);
	mlx_hook(app.window, 2, 1L<<0, press_key, &app.keyboard);
	mlx_hook(app.window, 3, 1L<<1, release_key, &app.keyboard);
	mlx_hook(app.window, 6, 1L<<6, player_mouse, &app);
	mlx_loop_hook(app.mlx, app_loop, &app);
	mlx_loop(app.mlx);
	mlx_destroy_image(app.mlx, app.img.data);
	mlx_destroy_window(app.mlx, app.window);
	mlx_destroy_display(app.mlx);
	return (0);
}
