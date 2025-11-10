/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/10 15:26:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline
void	render_fdf_horizontal_lines(t_image *img, t_fdf *fdf, t_linedrawer *drawline)
{
	const t_map	*map = fdf->map;
	size_t		offset;
	t_point		p;
	t_point		prev;
	t_point		curr;

	p.y = -1;
	while (++p.y < map->height)
	{
		p.x = 0;
		prev = fdf->transformed[map->width * p.y + p.x];
		while (++p.x < map->width)
		{
			offset = map->width * p.y + p.x;
			curr = fdf->transformed[offset];
			drawline(img, prev, curr, map->color[offset]);
			prev = curr;
		}
	}
}

static inline
void	render_fdf_vertical_lines(t_image *img, t_fdf *fdf, t_linedrawer *drawline)
{
	const t_map	*map = fdf->map;
	size_t		offset;
	t_point		p;
	t_point		prev;
	t_point		curr;

	p.x = -1;
	while (++p.x < map->width)
	{
		p.y = 0;
		prev = fdf->transformed[map->width * p.y + p.x];
		while (++p.y < map->height)
		{
			offset = map->width * p.y + p.x;
			curr = fdf->transformed[offset];
			drawline(img, prev, curr, map->color[offset]);
			prev = curr;
		}
	}
}

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
			fdf->transformed[i++] = (t_point){new.x + fdf->position.x, new.y + fdf->position.y};
			p.x += fdf->spacing;
		}
		p.y += fdf->spacing;
	}
}

void	render_fdf(t_image *img, t_fdf *fdf, t_linedrawer *drawline)
{
	transform_fdf_points(fdf);
	if (fdf->map->width == 1 && fdf->map->height == 1)
		return (putpixel(img, fdf->transformed[0].x, fdf->transformed[0].y, WHITE));
	render_fdf_horizontal_lines(img, fdf, drawline);
	render_fdf_vertical_lines(img, fdf, drawline);
}
