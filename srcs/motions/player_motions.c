/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_motions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:56:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/12 16:38:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include <math.h>

void	move_player(t_player *player, double sine, double cosine, t_map *map)
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
		player->floor = next.z;
	}
}

void	rotate_player(t_player *player, double rotation)
{
	const int	zfar = player->cam->zfar;
	double		angle;
	double		fx;
	double		fy;
	t_fov		*fov;

	player->angle += rotation * player->sensibility;
	angle = player->angle;
	player->axis_y = (t_trig){sin(angle), cos(angle)};
	angle += QUADRANT;
	player->axis_x = (t_trig){sin(angle), cos(angle)};
	fov = &player->cam->fov;
	fx = player->axis_y.cos * zfar;
	fy = player->axis_y.sin * zfar;
	fov->plx = fx + fy;
	fov->ply = fy - fx;
	fov->prx = fx - fy;
	fov->pry = fy + fx;
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
		move_player(player, axis_y.sin, axis_y.cos, map);
	if (keyboard & KEY_S)
		move_player(player, -axis_y.sin, -axis_y.cos, map);
	if (keyboard & KEY_D)
		move_player(player, axis_x.sin, axis_x.cos, map);
	if (keyboard & KEY_A)
		move_player(player, -axis_x.sin, -axis_x.cos, map);
	if (keyboard & ARROW_RIGHT)
		rotate_player(player, 1);
	if (keyboard & ARROW_LEFT)
		rotate_player(player, -1);
	if (player->floor == player->position->z && keyboard & SPACE)
		player->zforce = vox->world->unity * 10;
	return (0);
}
