/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:48:00 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 12:16:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "parsers.h"
#include "mlx.h"

int	init_app(t_app *app, char **argv, int width, int height)
{
	*app = (t_app){};
	app->mlx = mlx_init();
	if (!app->mlx)
		return (ERROR);
	app->window = mlx_new_window(app->mlx, width, height, "fdf");
	if (!app->window)
		return (free_app(app, NULL), ERROR);
	if (init_img(app->mlx, &app->img, width, height) < 0)
		return (free_app(app, NULL), ERROR);
	if (!(parse_arguments(argv, &app->map, &app->vox.sky, 0) & MAP_DONE))
	 	return (free_app(app, NULL), ERROR);
	if (init_fdf(&app.fdf, (t_pos){width >> 1, height >> 1}, &
}
