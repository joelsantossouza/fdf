/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/13 14:22:16 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include <math.h>

static inline
void	raymarching(t_image *img, t_map *map, t_camera *cam, t_ray *ray)
{
	size_t		offset;
	unsigned	color;
	int			new_height;
	int			i;

	i = 0;
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
		if (new_height < ray->max_height)
		{
			color = map->color[offset];
			while (ray->max_height > new_height)
				putpixel(img, ray->column, --ray->max_height, color);
		}
	}
}

static inline
void	put_background(t_image *img, t_ray *ray, t_camera *cam, t_pic *sky)
{
	const int	horizon = cam->horizon;
	const int	max_height = ray->max_height;
	t_point		texture;
	t_dpoint	angle;
	int			i;

	angle.x = atan2(ray->dy, ray->dx);
	texture.x = (int)(angle.x / CIRCLE * sky->width);
	i = -1;
	while (++i < max_height)
	{
		angle.y = (atan2(horizon - i, cam->zfar) + QUADRANT) / PI;
		texture.y = (int)(angle.y * sky->height);
		putpixel(img, ray->column, i, sky->data[sky->width * texture.y + texture.x]);
	}
}

void	render_voxelspace(t_image *img, t_map *map, t_camera *cam, t_pic *sky)
{
	t_ray			ray;
	const int		width = img->width;
	const t_fov		fov = cam->fov;
	const int		zfar = cam->zfar;
	const t_dpoint	position = cam->position;

	ray.column = -1;
	while (++ray.column < width)
	{
		ray.x = position.x;
		ray.y = position.y;
		ray.dx = (fov.plx + (fov.prx - fov.plx) / width * ray.column) / zfar;
		ray.dy = (fov.ply + (fov.pry - fov.ply) / width * ray.column) / zfar;
		ray.max_height = img->height;
		raymarching(img, map, cam, &ray);
		put_background(img, &ray, cam, sky);
	}
}
