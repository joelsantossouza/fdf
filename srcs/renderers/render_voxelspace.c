/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/11 16:38:00 by joesanto         ###   ########.fr       */
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
		ray->x += ray->dx;
		ray->y += ray->dy;
		if (ray->x < 0 || ray->x >= map->width || ray->y < 0 || ray->y >= map->height)
			break ;
		offset = map->width * (int)ray->y + (int)ray->x;
		new_height = (cam->position.z - map->altitude[offset]) / i + cam->horizon;
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
		ray.dx = (fov.plx + (fov.prx - fov.plx) / width * ray.column) / zfar;
		ray.dy = (fov.ply + (fov.pry - fov.ply) / width * ray.column) / zfar;
		ray.x = position.x;
		ray.y = position.y;
		raymarching(img, map, cam, &ray);
	}
}
