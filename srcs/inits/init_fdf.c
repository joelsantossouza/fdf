/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:00:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 23:12:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"
#include <stdlib.h>
#include <math.h>

int	init_fdf(t_fdf *fdf, t_pos pos, t_map *map, t_img *img)
{
	t_axis	*axis;
	t_dpos2	hypotenuse;

	fdf->data = malloc(sizeof(*fdf->data) * map->total);
	if (!fdf->data)
		return (*fdf = (t_fdf){}, ERROR);
	axis = &fdf->axis;
	hypotenuse.x = sqrt(map->width * map->width + map->height * map->height);
	hypotenuse.y = sqrt(img->width * img->width + img->height * img->height);
	fdf->center.x = -((map->width >> 1) * 15);
	fdf->center.y = -((map->height >> 1) * 15);
	fdf->pos = pos;
	// FIX ISOMETRIC PROJECTION AND ZOOM
	axis->angle_x = 0;
	axis->x = (t_trig){0, 1};
	axis->angle_y = 0.7853981634;
	axis->y = (t_trig){0.70710678, 0.70710678};
	axis->angle_z = 0.6154729074;
	axis->z = (t_trig){0.57734472, 0.81650051};
	fdf->drawline = bresenham_drawline;
	fdf->zoom = 1;
	fdf->max_zoom = hypotenuse.y / (hypotenuse.x * 0.5);
	fdf->min_zoom = 0.02;
	fdf->spacing = 15;
	fdf->scale = 1;
	return (SUCCESS);
}
