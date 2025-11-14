/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_motions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:56:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/14 21:16:06 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include <math.h>

void	player_walk(t_player *player, double sine, double cosine, t_map *map)
{
	const int	width = map->width;
	const int	height = map->height;
	t_dpoint3	*pos;
	t_dpoint3	next;
	double		height_difference;

	pos = player->pos;
	next.x = pos->x + cosine * player->speed;
	next.y = pos->y + sine * player->speed;
	if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height)
		return ;
	next.z = map->altitude[width * (int)next.y + (int)next.x] + player->height;
	height_difference = next.z - pos->z;
	if (height_difference <= player->climb_max)
	{
		if (height_difference > 0)
			pos->z = next.z;
		pos->x = next.x;
		pos->y = next.y;
		player->floor = next.z;
	}
}

void	player_fly(t_player *player, double sine, double cosine, t_map *map)
{
	t_dpoint3	*pos;
	t_dpoint2	next;
	
	pos = player->pos;
	next.x = pos->x + cosine * player->speed;
	next.y = pos->y + sine * player->speed;
	if (next.x >= 0 && next.x < map->width && next.y >= 0 && next.y < map->height)
	{
		pos->x = next.x;
		pos->y = next.y;
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

int	player_motions(t_vox *vox, void (*move_func)())
{
	const t_trig	axis_y = vox->player->axis_y;
	const t_trig	axis_x = vox->player->axis_x;
	const int		keyboard = vox->keyboard;
	t_player		*player;
	t_map			*map;

	player = vox->player;
	map = vox->map;
	if (keyboard & KEY_W)
		move_func(player, axis_y.sin, axis_y.cos, map);
	if (keyboard & KEY_S)
		move_func(player, -axis_y.sin, -axis_y.cos, map);
	if (keyboard & KEY_D)
		move_func(player, axis_x.sin, axis_x.cos, map);
	if (keyboard & KEY_A)
		move_func(player, -axis_x.sin, -axis_x.cos, map);
	// RESPONSIBLE VALUES HERE!
	if ((player->floor == player->pos->z || move_func == player_fly) && (keyboard & SPACE))
		player->zforce = vox->world->unity * 10;
	return (0);
}
