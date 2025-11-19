/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf_test.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 10:51:38 by joesanto         ###   ########.fr       */
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
	t_app app;

	(void)argc;
	if (!(parse_arguments(argv, &app.map, &app.vox.sky, 0) & MAP_DONE))
	{
		free_map(&app.map, NULL);
		free_pic(&app.vox.sky, NULL);
		ft_fprintf(2, "Fail to parse arguments\n");
		return (1);
	}
	app.mlx = mlx_init();
	if (!app.mlx)
		return (1);
	app.window = mlx_new_window(app.mlx, WIDTH, HEIGHT, "Bresenham test");
	if (!app.window)
		return (2);
	if (init_img(app.mlx, &app.img, WIDTH, HEIGHT) < 0)
		return (1);
	if (init_fdf(&app.fdf, (t_pos){WIDTH >> 1, HEIGHT >> 1}, &app.map, &app.img) < 0)
		return (1);
	if (init_player(&app.vox.player, 10, 2, &app.map) < 0)
		return (1);
	app.vox.gravity = 0.0096;
	app.vox.min_horizon = -HEIGHT + (HEIGHT / 1.5);
	app.vox.max_horizon = HEIGHT + (HEIGHT >>1);
	app.keyboard = 0;
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
