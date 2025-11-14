/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/14 20:23:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include <math.h>

static inline
void	raymarching(t_image *img, t_map *map, t_camera *cam, t_ray *ray)
{
	const int		width = map->width;
	size_t			offset;
	unsigned int	color;
	int				new_height;
	int				i;

	i = 0;
	while (++i < cam->zfar && ray->max_height > 0)
	{
		ray->x += ray->dx;
		ray->y += ray->dy;
		if (ray->x < 0 || ray->x >= width || ray->y < 0 || ray->y >= map->height)
			break ;
		offset = width * (int)ray->y + (int)ray->x;
		new_height = (cam->pos.z - map->altitude[offset]) / i + cam->horizon;
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
	t_dpoint2	angle;
	t_point		texture;
	int			i;

	angle.x = atan2(ray->dy, ray->dx);
	texture.x = (int)(angle.x / CIRCLE * sky->width) % sky->width;
	i = -1;
	while (++i < max_height)
	{
		angle.y = (atan2(horizon - i, cam->zfar) + QUADRANT) / PI;
		texture.y = (int)(angle.y * sky->height);
		putpixel(img, ray->column, i, sky->data[sky->width * texture.y + texture.x]);
	}
}

static inline
void	fill_black_column(t_image *img, int x, int y)
{
	const int		linelen = img->linelen / sizeof(int);
	unsigned int	*ptr;

	ptr = (unsigned int *)((img->bpp >> 3) * x + img->linelen * y + img->addr);
	while (y-- > 0)
	{
		*ptr = BLACK;
		ptr -= linelen;
	}
}

void	render_voxelspace(t_image *img, t_map *map, t_camera *cam, t_pic *sky)
{
	t_ray			ray;
	const int		has_sky = sky != 0 && sky->data != 0;
	const t_fov		*fov = &cam->fov;
	const double	zfar = 1.0 / cam->zfar;
	const t_dpoint2	fov_delta = {
		(fov->prx - fov->plx) / img->width,
		(fov->pry - fov->ply) / img->width,
	};

	ray.column = -1;
	while (++ray.column < img->width)
	{
		ray.x = cam->pos.x;
		ray.y = cam->pos.y;
		ray.dx = (fov->plx + fov_delta.x * ray.column) * zfar;
		ray.dy = (fov->ply + fov_delta.y * ray.column) * zfar;
		ray.max_height = img->height;
		raymarching(img, map, cam, &ray);
		if (has_sky)
			put_background(img, &ray, cam, sky);
		else
			fill_black_column(img, ray.column, ray.max_height);
	}
}
