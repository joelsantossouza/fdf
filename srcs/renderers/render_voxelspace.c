/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:36:58 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/07 14:52:16 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_voxelspace(t_image *image, t_voxelspace *vox, t_camera *camera)
{
	int		i;
	int		z;
	int		max_height;
	int		new_height;
	unsigned int color;
	t_angle	delta;
	t_point	p;

	i = -1;
	while (++i < image->width)
	{
		delta.x = (-camera->zfar + (camera->zfar * 2) / (double) image->width * i) / (double) camera->zfar;
		delta.y = (camera->zfar + (0) / (double) image->width * i) / (double) camera->zfar;
		z = 0;
		max_height = 0;
		p = camera->position;
		while (++z < camera->zfar)
		{
			p = (t_point){p.x + delta.x, p.y + delta.y};
			if (p.x < 0 || p.x >= vox->map->width || p.y < 0 || p.y >= vox->map->height)
				break ;
			new_height = vox->map->altitude[vox->map->width * p.y + p.x] - camera->altitude / z * vox->scale;
			if (new_height >= image->height)
				new_height = image->height - 1;
			if (new_height > max_height)
			{
				color = vox->map->altitude[vox->map->width * p.y + p.x];
				while (max_height < new_height)
					putpixel(image, i, ++max_height, color);
			}
		}
	}
}
