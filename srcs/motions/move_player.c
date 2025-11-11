/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:56:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/11 17:24:06 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"

void move_player(t_player *player, t_trig *angle, t_map *map)
{
	const int	width = map->width;
	const int	height = map->height;
	t_dpoint	*position;
	t_dpoint	next;
	double		height_difference;

	position = player->position;
	next.x = position->x + angle->cos * player->speed;
	next.y = position->y + angle->sin * player->speed;
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
