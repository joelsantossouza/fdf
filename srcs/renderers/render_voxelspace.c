/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 13:48:03 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"

void	render_voxelspace(t_image *img, t_map *map, t_camera *cam)
{
	int			i;
	t_vector	delta;
	const t_dpoint	pl = {
		cam->angle.cos * cam->zfar + cam->angle.sin * cam->zfar,
		cam->angle.sin * cam->zfar - cam->angle.cos * cam->zfar,
	};
	const t_dpoint	pr = {
		cam->angle.cos * cam->zfar - cam->angle.sin * cam->zfar,
		cam->angle.sin * cam->zfar + cam->angle.cos * cam->zfar,
	};

	i = -1;
	while (++i < img->width)
	{
		delta.x = (pl.x + (pr.x - pl.x) / img->width * i) / cam->zfar;
		delta.y = (pl.y + (pr.y - pl.y) / img->width * i) / cam->zfar;

		//DELETEME
		t_dpoint	ray;
		ray.x = cam->position.x;
		ray.y = cam->position.y;
		int z = 0;
		int	max_height = img->height;
		while (++z < cam->zfar)
		{
			ray.x += delta.x;
			ray.y += delta.y;
			size_t	offset = (map->width * (int)ray.y + (int)ray.x);
			int new_height = (cam->altitude - map->altitude[offset]) * cam->scale / z + cam->horizon;
			if (new_height < 0)
				new_height = 0;
			if (new_height < max_height)
			{
				unsigned color = map->color[offset];
				while (max_height > new_height)
					putpixel(img, i, --max_height, color);
			}
		}
	}
}
