/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 12:30:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <math.h>
#include "../../events/events.h"
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

void	*mlx;
void	*window;
t_image	image;
t_map	map;
double anglex = 0;
double angley = 0;
double anglez = 0;

int     app_loop_test(t_app *app)
{
        const int       keyboard = app->keyboard;
        t_map           *map;
        t_vox           *vox;
        t_player        *player;
        t_fdf           *fdf;

        map = app->map;
        global_events(app);
        if (keyboard & TAB)
        {
                player = app->vox->player;
                vox = app->vox;
                player_events(player, map, app->fps, keyboard);
                player_physics(player, vox->gravity * app->fps);
                render_voxelspace(app->img, map, player->cam, vox->sky);
        }
        else
        {
                fdf = app->fdf;
                fdf_events(fdf, app->fps, keyboard);
                render_fdf(app->img, fdf, map);
        }
        mlx_put_image_to_window(app->mlx, app->window, app->img->data, 0, 0);
        return (0);
}

int	main(int argc, char **argv)
{
	int	temp;
	t_fdf	fdf;
	t_pic	sky;

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
			return (2);
		}
	}
	else if (argc == 4)
	{
		if (parse_voxel_file(argv[1], argv[2], &map) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
		if (parse_picture(argv[3], &sky.data, &sky.width, &sky.height) < 0)
		{
			ft_fprintf(2, "Fail to load sky\n");
			return (2);
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
	image.bpp >>= 3;
	image.center = (t_point){WIDTH >>1, HEIGHT >>1};
	fdf.scale = 1;
	fdf.center.x = -(map.width / 2 * 15);
	fdf.center.y = -(map.height / 2 * 15);
	fdf.pos.x = WIDTH / 2;
	fdf.pos.y = HEIGHT / 2;
	fdf.spacing = 15;
	fdf.zoom = 1;
	double map_diag = sqrt(map.width * map.width + map.height + map.height);
	double screen_diag = sqrt(image.width * image.width + image.height * image.height);
	fdf.min_zoom = 0.02;
	fdf.max_zoom = screen_diag / (map_diag  *  0.5);
	fdf.drawline = bresenham_drawline;
	fdf.axis.angle_x = 0;
	fdf.axis.angle_y = 0;
	fdf.axis.angle_z = 0;
	fdf.axis.x.cos = cos(0);
	fdf.axis.x.sin = sin(0);
	fdf.axis.y.cos = cos(0);
	fdf.axis.y.sin = sin(0);
	fdf.axis.z.cos = cos(0);
	fdf.axis.z.sin = sin(0);
	fdf.transformed = malloc(sizeof(t_point) * map.total);
	if (!fdf.transformed)
		return (3);
	t_camera camera = (t_camera){
		.pos.x = map.width / 2.0,
		.pos.y = map.height / 5.0,
		.pos.z = 300,
		.horizon = image.height >> 1,
		.zfar = 11000,
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
	t_player player = (t_player){
		.pos = &camera.pos,
		.cam = &camera,
		.speed = 1,
		.move = player_walk,
		.stats = &stats,
	};
	player.floor = map.altitude[map.width * (int)player.pos->y + (int)player.pos->x] + player.stats->height;
	t_vox vox = {
		.player = &player,
		.gravity = 0.0096,
		.min_horizon = -HEIGHT + (HEIGHT / 1.5),
		.max_horizon = HEIGHT + (HEIGHT >>1),
	};
	t_app app = {
		.mlx = mlx,
		.window = window,
		.img = &image,
		.map = &map,
		.fdf = &fdf,
		.vox = &vox,
		.keyboard = 0,
	};
	rotate_player(&player, 0);
	mlx_mouse_hide(mlx, window);
	mlx_hook(window, 2, 1L<<0, press_key, &app.keyboard);
	mlx_hook(window, 3, 1L<<1, release_key, &app.keyboard);
	mlx_hook(window, 6, 1L<<6, player_mouse, &app);
	mlx_loop_hook(mlx, app_loop_test, &app);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
