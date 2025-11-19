/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fdf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:00:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 16:44:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"
#include "inits.h"
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
	fdf->center.x = -((map->width >> 1) * SPACING);
	fdf->center.y = -((map->height >> 1) * SPACING);
	fdf->pos = pos;
	// FIX ISOMETRIC PROJECTION AND ZOOM
	axis->angle_x = 0.392699081;
	axis->x = (t_trig){0.38268343, 0.92387953};
	axis->angle_y = -0.523598775;
	axis->y = (t_trig){-0.5, 0.8660254};
	axis->angle_z = 0.628318530;
	axis->z = (t_trig){0.58778525, 0.80901699};
	fdf->drawline = bresenham_drawline;
	fdf->zoom = 1;
	fdf->max_zoom = hypotenuse.y / (hypotenuse.x * 0.5);
	fdf->min_zoom = 0.02;
	fdf->spacing = SPACING;
	fdf->scale = 1;
	return (SUCCESS);
}
