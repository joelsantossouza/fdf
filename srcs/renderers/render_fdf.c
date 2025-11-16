/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/16 18:31:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline
void	transform_fdf_points(t_fdf *fdf)
{
	long			i;
	t_point			p;
	t_point			new;
	const t_point	center = fdf->center;
	const t_point	end = {
		center.x + fdf->map->width * fdf->spacing,
		center.y + fdf->map->height * fdf->spacing,
	};

	i = 0;
	p.y = center.y;
	while (p.y < end.y)
	{
		p.x = center.x;
		while (p.x < end.x)
		{
			new = rotate(&fdf->axis, p.x, p.y, fdf->map->altitude[i]);
			fdf->transformed[i].x = new.x * fdf->zoom + fdf->pos.x;
			fdf->transformed[i++].y = new.y * fdf->zoom + fdf->pos.y;
			p.x += fdf->spacing;
		}
		p.y += fdf->spacing;
	}
}

void	render_fdf(t_image *img, t_fdf *fdf, t_linedrawer *drawline)
{
	const t_map	*map = fdf->map;
	const int	width = map->width;
	t_point			p;
	unsigned int	color;
	size_t			offset;

	transform_fdf_points(fdf);
	if (width == 1 && map->height == 1)
		return (putpixel(img, fdf->transformed[0].x, fdf->transformed[0].y, map->color[0]));
	p.y = 0;
	while (p.y < map->total)
	{
		p.x = -1;
		while (++p.x < width)
		{
			offset = p.y + p.x;
			color = map->color[offset];
			if (p.x + 1 < width)
				drawline(img, fdf->transformed[offset], fdf->transformed[offset + 1], color);
			if (p.y + width < map->total)
				drawline(img, fdf->transformed[offset], fdf->transformed[offset + width], color); 
		}
		p.y += width;
	}
}
