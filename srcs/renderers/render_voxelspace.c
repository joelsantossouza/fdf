/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/10 20:30:53 by joesanto         ###   ########.fr       */
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
		if (ray->position.x < 0 || ray->position.x >= map->width || ray->position.y < 0 || ray->position.y >= map->height)
			break ;
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
	const t_fov		fov = cam->fov;
	const int		zfar = cam->zfar;
	const t_dpoint	position = cam->position;

	ray.column = -1;
	while (++ray.column < width)
	{
		ray.direction.x = (fov.plx + (fov.prx - fov.plx) / width * ray.column) / zfar;
		ray.direction.y = (fov.ply + (fov.pry - fov.ply) / width * ray.column) / zfar;
		ray.position.x = position.x;
		ray.position.y = position.y;
		raymarching(img, map, cam, &ray);
	}
}
