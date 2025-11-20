/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:56:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 16:02:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include "events.h"
#include "mlx.h"

int	app_loop(t_app *app)
{
	const int	keyboard = app->keyboard;
	t_map		*map;
	t_vox		*vox;
	t_player	*player;
	t_img		*img;

	map = &app->map;
	img = &app->img;
	global_events(app->mlx, &app->fdf, &app->vox, app->keyboard);
	if (keyboard & TAB)
	{
		player = &app->vox.player;
		vox = &app->vox;
		player_events(player, map, keyboard);
		voxelspace_physics(player, vox->gravity);
		render_voxelspace(img, map, &player->cam, &vox->sky);
		mlx_mouse_move(app->mlx, app->window, img->center.x, img->center.y);
	}
	else
	{
		fdf_events(&app->fdf, keyboard);
		render_fdf(img, &app->fdf, map);
	}
	mlx_put_image_to_window(app->mlx, app->window, img->data, 0, 0);
	return (0);
}
