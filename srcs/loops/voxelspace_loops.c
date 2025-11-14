/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace_loops.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 19:48:45 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/14 21:00:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "mlx.h"

int	voxelspace_walk_loop(t_vox *vox)
{
	t_player	*player;
	t_image		*img;

	player = vox->player;
	img = vox->img;
	player_motions(vox, player_walk);
	gravity(&player->pos->z, &player->zforce, player->floor, vox->world->gravity);
	render_voxelspace(img, vox->map, player->cam, vox->sky);
	mlx_put_image_to_window(vox->mlx, vox->window, img->data, 0, 0);
	return (0);
}
