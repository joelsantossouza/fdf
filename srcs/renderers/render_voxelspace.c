/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:36:58 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/08 13:40:32 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

typedef struct s_scene
{
	t_map	*map;
	t_camera *camera;
	t_image	*image;
}	t_scene;

static inline
void	draw_column(t_scene *scene, int column, int *max_height, t_point p, int z)
{
	int	new_height;
	unsigned color;
	const long	offset = scene->map->width * p.y + p.x;

	new_height = (scene->camera->altitude - scene->map->altitude[offset]) * 200 / z + scene->image->height / 2;
	if (new_height < 0)
		new_height = 0;
	if (new_height < *max_height)
	{
		color = scene->map->color[offset];
		while (*max_height > new_height)
			putpixel(scene->image, column, --(*max_height), color);
	}
}

static inline
void	render_vox_column_horizontal(t_scene *scene, int column, t_point p0, t_point p1)
{
	const t_point	delta = {p1.x - p0.x, p1.y - p0.y};
	const int		dir = 1 - 2 * (delta.y < 0);
	const t_point	inc = {delta.x<<1, (delta.y * dir)<<1};
	int				decision;
	int				max_height;
	int				i;

	max_height = scene->image->height;
	decision = inc.y - delta.x;
	i = 0;
	while (p0.x <= p1.x && ++i)
	{
		if (decision >= 0)
		{
			p0.y += dir;
			decision -= inc.x;
		}
		if (p0.x < 0 || p0.x >= scene->map->width || p0.y < 0 || p0.y >= scene->map->height)
			break ;
		p0.x++;
		decision += inc.y;
		draw_column(scene, column, &max_height, p0, i);
	}
}

static inline
void	render_vox_column_vertical(t_scene *scene, int column, t_point p0, t_point p1)
{
	const t_point	delta = {p1.x - p0.x, p1.y - p0.y};
	const int		dir = 1 - 2 * (delta.x < 0);
	const t_point	inc = {(delta.x * dir)<<1, delta.y<<1};
	int				decision;
	int				max_height;
	int				i;

	max_height = scene->image->height;
	decision = inc.x - delta.y;
	i = 0;
	while (p0.y <= p1.y && ++i)
	{
		if (decision >= 0)
		{
			p0.x += dir;
			decision -= inc.y;
		}
		if (p0.x < 0 || p0.x >= scene->map->width || p0.y < 0 || p0.y >= scene->map->height)
			break ;
		p0.y++;
		decision += inc.x;
		draw_column(scene, column, &max_height, p0, i);
	}
}

static inline
int	render_vox_column(t_scene *scene, int column, t_point p0, t_point p1)
{
	//if (liangbarsky_clipping(&p0, &p1, image->width - 1, image->height - 1) < 0)
	//	return (-1);
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			render_vox_column_horizontal(scene, column, p0, p1);
		else
			render_vox_column_horizontal(scene, column, p1, p0);
	}
	else
	{
		if (p0.y <= p1.y)
			render_vox_column_vertical(scene, column, p0, p1);
		else
			render_vox_column_vertical(scene, column, p1, p0);
	}
	return (0);
}

#include <math.h>
void	render_voxelspace(t_image *image, t_voxelspace *vox, t_camera *camera)
{
	int	i;
	t_scene	scene = {.map = vox->map, .camera = camera, .image = image};
	t_point	bleft = {
		camera->position.x - camera->zfar,
		camera->position.y + camera->zfar,
	};
	t_point bright = {
		camera->position.x + camera->zfar,
		camera->position.y + camera->zfar,
	};
	t_point left;
	double inc = (bright.x - bleft.x) / (double) image->width;

	i = -1;
	left.y = bleft.y;
	while (++i < image->width)
	{
		left.x = round(bleft.x + i * inc);
		render_vox_column(&scene, i, camera->position, left);
	}
}
