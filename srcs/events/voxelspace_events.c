/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:58:18 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 13:37:50 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "events.h"
#include "mlx.h"
#include <sys/time.h>

int	player_mouse(int x, int y, t_vox *vox)
{
	const t_point	center = vox->img->center;
	const t_point	delta = {x - center.x, y - center.y};
	const t_physic	*world = vox->world;
	t_camera		*cam;
	int				nxt_horizon;

	rotate_player(vox->player, delta.x);
	cam = vox->player->cam;
	nxt_horizon = cam->horizon - delta.y;
	if (nxt_horizon >= world->min_horizon && nxt_horizon <= world->max_horizon)
		cam->horizon = nxt_horizon;
	mlx_mouse_move(vox->mlx, vox->window, center.x, center.y);
	return (0);
}

int	player_events(t_vox *vox)
{
	const t_trig	axis_y = vox->player->axis_y;
	const t_trig	axis_x = vox->player->axis_x;
	const int		keyboard = vox->keyboard;
	t_player		*player;
	t_map			*map;

	player = vox->player;
	map = vox->map;
	if (keyboard & KEY_W)
		player->move(player, axis_y.sin, axis_y.cos, map);
	if (keyboard & KEY_S)
		player->move(player, -axis_y.sin, -axis_y.cos, map);
	if (keyboard & KEY_D)
		player->move(player, axis_x.sin, axis_x.cos, map);
	if (keyboard & KEY_A)
		player->move(player, -axis_x.sin, -axis_x.cos, map);
	if ((keyboard & SPACE) && (player->floor == player->pos->z || player->move == player_fly))
		player->zforce = player->stats->jump_force;
	if (keyboard & CTRL)
		player->zforce -= player->stats->dive_force;
	if (keyboard & SHIFT)
		player->speed = player->stats->run_speed_max;
	else
		player->speed = player->stats->speed_max;
	return (0);
}
