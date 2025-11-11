/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:56:54 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/11 16:34:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"

void move(t_dpoint *position, t_motion *motion, int myheight, t_map *map)
{
	const t_trig	angle = motion->angle;
	const int		width = map->width;
	const int		height = map->height;
	t_dpoint		next;
	double			height_difference;

	next.x = position->x + angle.cos * motion->speed;
	next.y = position->y + angle.sin * motion->speed;
	if (next.x < 0 || next.x >= width || next.y < 0 || next.y >= height)
		return ;
	next.z = map->altitude[map->width * (int)next.y + (int)next.x] + myheight;
	height_difference = next.z - position->z;
	if (height_difference <= motion->climb_max)
	{
		if (height_difference > 0)
			position->z = next.z;
		position->x = next.x;
		position->y = next.y;
	}
}
