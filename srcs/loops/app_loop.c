/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_loop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:56:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/16 23:44:42 by joesanto         ###   ########.fr       */
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
	t_fdf		*fdf;

	//if (keyboard & ESC)
	//	mlx_loop_end(app->mlx);
	map = app->map;
	if (keyboard & TAB)
	{
		player = app->vox->player;
		vox = app->vox;
		player_events(player, map, keyboard);
		player_physics(player, vox->gravity);
		render_voxelspace(app->img, map, player->cam, vox->sky);
	}
	else
	{
		fdf = app->fdf;
		fdf_events(fdf, keyboard);
		render_fdf(app->img, fdf, map);
	}
	mlx_put_image_to_window(app->mlx, app->window, app->img->data, 0, 0);
	return (0);
}
