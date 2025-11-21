/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:48:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/21 10:24:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "parsers.h"
#include "inits.h"

#include "mlx.h"

int	init_app(t_app *app, char **argv, int width, int height)
{
	*app = (t_app){};
	if (!(parse_arguments(argv, &app->map, &app->vox.sky, 0) & MAP))
		return (free_app(app, NULL), ERROR);
	app->mlx = mlx_init();
	if (!app->mlx)
		return (free_app(app, NULL), ERROR);
	app->window = mlx_new_window(app->mlx, width, height, "fdf");
	if (!app->window)
		return (free_app(app, NULL), ERROR);
	if (init_img(app->mlx, &app->img, width, height) < 0)
		return (free_app(app, NULL), ERROR);
	if (init_fdf(&app->fdf, (t_pos){width >> 1, height >> 1},
		&app->map, &app->img) < 0)
		return (free_app(app, NULL), ERROR);
	init_player(&app->vox.player, PLAYER_HEIGHT, WALK_SPEED, &app->map);
	app->vox.gravity = GRAVITY;
	app->vox.min_horizon = -height + (height / 1.5);
	app->vox.max_horizon = height + (height >> 1);
	app->keyboard = 0;
	return (SUCCESS);
}
