/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 21:56:36 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/14 22:10:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "mlx.h"

int	voxelspace_loop(t_vox *vox)
{
	t_player	*player;
	t_image		*img;

	player = vox->player;
	player_motions(vox);
	gravity(&player->pos->z, &player->zforce, player->floor, vox->world->gravity);
	render_voxelspace(img, vox->map, player->cam, vox->sky);
	mlx_put_image_to_window(vox->mlx, vox->window, img->data, 0, 0);
	return (0);
}
