/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 10:17:47 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 10:49:44 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "inits.h"
#include "parsers.h"

int	init_player(t_player *player, double height, double walk_speed, t_map *map)
{
	const t_pos	center = {map->width >> 1, map->height >> 1};

	player->floor = map->altitude[map->width * center.y + center.x];
	player->cam.pos = (t_dpos3){center.x, center.y, player->floor + height * 42};
	player->cam.horizon = 0;
	player->cam.zfar = ZFAR;
	player->cam.scale = 300;
	player->pos = &player->cam.pos;
	player->stats.height = height;
	player->stats.walk_speed = walk_speed;
	player->stats.run_speed = walk_speed * 2;
	player->stats.climb_max = height;
	player->stats.jump_force = height * 2;
	player->stats.dive_force = height * 2 - height * 2 / 5;
	player->stats.sensibility = SENSIBILITY;
	player->move = player_fly;
	player->angle = 0;
	rotate_player(player, 0);
	return (SUCCESS);
}
