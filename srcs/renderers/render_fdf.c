/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/16 19:54:00 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline
void	transform_fdf_points(t_fdf_stats *fdf_stats, t_map *map)
{
	long			i;
	t_point			p;
	t_point			new;
	const t_point	center = fdf_stats->center;
	const t_point	end = {
		center.x + map->width * fdf_stats->spacing,
		center.y + map->height * fdf_stats->spacing,
	};

	i = 0;
	p.y = center.y;
	while (p.y < end.y)
	{
		p.x = center.x;
		while (p.x < end.x)
		{
			new = rotate(&fdf_stats->axis, p.x, p.y, map->altitude[i]);
			fdf_stats->transformed[i].x = new.x * fdf_stats->zoom + fdf_stats->pos.x;
			fdf_stats->transformed[i++].y = new.y * fdf_stats->zoom + fdf_stats->pos.y;
			p.x += fdf_stats->spacing;
		}
		p.y += fdf_stats->spacing;
	}
}

void	render_fdf(t_image *img, t_fdf_stats *fdf_stats, t_map *map)
{
	const int	width = map->width;
	const t_linedrawer	*drawline = fdf_stats->drawline;
	t_point			p;
	unsigned int	color;
	size_t			offset;

	transform_fdf_points(fdf_stats, map);
	if (width == 1 && map->height == 1)
		return (putpixel(img, fdf_stats->transformed[0].x, fdf_stats->transformed[0].y, map->color[0]));
	p.y = 0;
	while (p.y < map->total)
	{
		p.x = -1;
		while (++p.x < width)
		{
			offset = p.y + p.x;
			color = map->color[offset];
			if (p.x + 1 < width)
				drawline(img, fdf_stats->transformed[offset], fdf_stats->transformed[offset + 1], color);
			if (p.y + width < map->total)
				drawline(img, fdf_stats->transformed[offset], fdf_stats->transformed[offset + width], color); 
		}
		p.y += width;
	}
}
