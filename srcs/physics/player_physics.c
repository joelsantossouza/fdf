/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_physics.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 23:34:25 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/16 23:37:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"

void	player_physics(t_player *player, double gravity_force)
{
	if (player->move == player_walk)
		gravity(&player->pos->z, &player->zforce, player->floor, gravity_force);
	else if (player->zforce != 0)
	{
		player->pos->z += player->zforce;
		player->zforce = 0;
	}
}
