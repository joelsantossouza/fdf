/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_motions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:56:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/12 13:34:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include <math.h>

void	move_player(t_player *player, double cosine, double sine, t_map *map)
{
	const int	width = map->width;
	const int	height = map->height;
	t_dpoint	*position;
	t_dpoint	next;
	double		height_difference;

	position = player->position;
	next.x = position->x + cosine * player->speed;
	next.y = position->y + sine * player->speed;
	if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height)
		return ;
	next.z = map->altitude[width * (int)next.y + (int)next.x] + player->height;
	height_difference = next.z - position->z;
	if (height_difference <= player->climb_max)
	{
		if (height_difference > 0)
			position->z = next.z;
		position->x = next.x;
		position->y = next.y;
	}
}

void	rotate_player(t_player *player, double rotation)
{
	const int	zfar = player->cam->zfar;
	double		angle;
	t_trig		axis_y;
	t_fov		*fov;


	player->angle += rotation * player->sensibility;
	angle = player->angle;
	player->axis_y = (t_trig){cos(angle), sin(angle)};
	angle += QUADRANT;
	player->axis_x = (t_trig){cos(angle), sin(angle)};
	axis_y = player->axis_y;
	fov = &player->cam->fov;
	fov->plx = axis_y.cos * zfar + axis_y.sin * zfar;
	fov->ply = axis_y.sin * zfar - axis_y.cos * zfar;
	fov->plx = axis_y.cos * zfar - axis_y.sin * zfar;
	fov->ply = axis_y.sin * zfar + axis_y.cos * zfar;
}

int	player_motions(t_vox *vox)
{
	const t_trig	axis_y = vox->player->axis_y;
	const t_trig	axis_x = vox->player->axis_x;
	const int		keyboard = vox->keyboard;
	t_player		*player;
	t_map			*map;

	player = vox->player;
	map = vox->map;
	if (keyboard & KEY_W)
		move_player(player, axis_y.cos, axis_y.sin, map);
	if (keyboard & KEY_S)
		move_player(player, -axis_y.cos, -axis_y.sin, map);
	if (keyboard & KEY_D)
		move_player(player, axis_x.cos, axis_x.sin, map);
	if (keyboard & KEY_A)
		move_player(player, -axis_x.cos, -axis_x.sin, map);
	if (keyboard & ARROW_RIGHT)
		rotate_player(player, 1);
	if (keyboard & ARROW_LEFT)
		rotate_player(player, -1);
	return (0);
}
