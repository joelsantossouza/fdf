/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:36:21 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/14 10:11:23 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include "mlx.h"

int	press_key(int keycode, int *keyboard)
{
	if (keycode == 119)
		*keyboard |= KEY_W;
	else if (keycode == 115)
		*keyboard |= KEY_S;
	else if (keycode == 100)
		*keyboard |= KEY_D;
	else if (keycode == 97)
		*keyboard |= KEY_A;
	else if (keycode == 65363)
		*keyboard |= ARROW_RIGHT;
	else if (keycode == 65361)
		*keyboard |= ARROW_LEFT;
	else if (keycode == 32)
		*keyboard |= SPACE;
	return (0);
}

int	release_key(int keycode, int *keyboard)
{
	if (keycode == 119)
		*keyboard &= ~(KEY_W);
	else if (keycode == 115)
		*keyboard &= ~(KEY_S);
	else if (keycode == 100)
		*keyboard &= ~(KEY_D);
	else if (keycode == 97)
		*keyboard &= ~(KEY_A);
	else if (keycode == 65363)
		*keyboard &= ~(ARROW_RIGHT);
	else if (keycode == 65361)
		*keyboard &= ~(ARROW_LEFT);
	else if (keycode == 32)
		*keyboard &= ~(SPACE);
	return (0);
}

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
