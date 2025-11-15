/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:56:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 15:56:02 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "events.h"
#include "mlx.h"

int	voxelspace_loop(t_vox *vox)
{
	t_player	*player;
	t_image		*img;

	player = vox->player;
	img = vox->img;
	player_events(vox);
	if (player->move == player_walk)
		gravity(&player->pos->z, &player->zforce, player->floor, vox->world->gravity);
	else if (player->zforce != 0)
	{
		player->pos->z += player->zforce;
		player->zforce = 0;
	}
	render_voxelspace(img, vox->map, player->cam, vox->sky);
	mlx_put_image_to_window(vox->mlx, vox->window, img->data, 0, 0);
	return (0);
}
