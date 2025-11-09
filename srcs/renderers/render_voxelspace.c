/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 16:30:03 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"

static inline
void	raymarching(t_image *img, t_map *map, t_camera *cam, t_ray *ray)
{
	size_t		offset;
	unsigned	color;
	int			new_height;
	int			max_height;
	int			i;

	i = 0;
	max_height = img->height;
	while (++i < cam->zfar)
	{
		ray->position.x += ray->direction.x;
		ray->position.y += ray->direction.y;
		offset = map->width * (int)ray->position.y + (int)ray->position.x;
		new_height = (cam->altitude - map->altitude[offset]) * cam->scale / i + cam->horizon;
		if (new_height < 0)
			new_height = 0;
		if (new_height < max_height)
		{
			color = map->color[offset];
			while (max_height > new_height)
				putpixel(img, ray->column, --max_height, color);
		}
	}
}

void	render_voxelspace(t_image *img, t_map *map, t_camera *cam)
{
	t_ray			ray;
	const int		width = img->width;
	const t_trig	angle = cam->angle;
	const t_dpoint	pl = {
		angle.cos * cam->zfar + angle.sin * cam->zfar,
		angle.sin * cam->zfar - angle.cos * cam->zfar,
	};
	const t_dpoint	pr = {
		angle.cos * cam->zfar - angle.sin * cam->zfar,
		angle.sin * cam->zfar + angle.cos * cam->zfar,
	};

	ray.column = -1;
	while (++ray.column < width)
	{
		ray.direction.x = (pl.x + (pr.x - pl.x) / width * ray.column) / cam->zfar;
		ray.direction.y = (pl.y + (pr.y - pl.y) / width * ray.column) / cam->zfar;
		ray.position.x = cam->position.x;
		ray.position.y = cam->position.y;
		raymarching(img, map, cam, &ray);
	}
}
