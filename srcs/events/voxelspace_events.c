/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace_events.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 12:58:18 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/17 17:06:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "voxelspace.h"
#include "events.h"
#include "mlx.h"

int	player_mouse(int x, int y, t_app *app)
{
	const t_vox		*vox = app->vox;
	const t_point	center = app->img->center;
	const t_point	delta = {x - center.x, y - center.y};
	t_camera		*cam;
	int				nxt_horizon;

	if (ft_abs(delta.x) < 3 && ft_abs(delta.y) < 3)
		return (0);
	rotate_player(vox->player, delta.x);
	cam = vox->player->cam;
	nxt_horizon = cam->horizon - delta.y;
	if (nxt_horizon >= vox->min_horizon && nxt_horizon <= vox->max_horizon)
		cam->horizon = nxt_horizon;
	mlx_mouse_move(app->mlx, app->window, center.x, center.y);
	return (0);
}

static inline
void	handle_space_event(int keyboard, t_player *player)
{
	static int	was_released;

	if (keyboard & SPACE)
	{
		if (was_released && is_double_click(SPACE))
		{
			if (player->move == player_walk)
				player->move = player_fly;
			else
				player->move = player_walk;
		}
		else if (player->move == player_fly || player->floor == player->pos->z)
			player->zforce = player->stats->jump_force;
		was_released = 0;
	}
	else
		was_released = 1;
}

void	player_events(t_player *player, t_map *map, int keyboard)
{
	const t_trig			axis_y = player->axis_y;
	const t_trig			axis_x = player->axis_x;
	const t_moveplayer		move = player->move;
	const t_player_stats	*stats = player->stats;

	handle_space_event(keyboard, player);
	if (keyboard & KEY_W)
		move(player, axis_y.sin, axis_y.cos, map);
	if (keyboard & KEY_S)
		move(player, -axis_y.sin, -axis_y.cos, map);
	if (keyboard & KEY_D)
		move(player, axis_x.sin, axis_x.cos, map);
	if (keyboard & KEY_A)
		move(player, -axis_x.sin, -axis_x.cos, map);
	if (keyboard & CTRL)
		player->zforce -= stats->dive_force;
	if (keyboard & SHIFT)
		player->speed = stats->run_speed_max;
	else
		player->speed = stats->speed_max;
}
