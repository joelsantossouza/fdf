/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 14:21:14 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static inline
void	transform_fdf_points(t_fdf *fdf, t_map *map)
{
	long		i;
	t_pos		p;
	t_pos		new;
	const t_pos	center = fdf->center;
	const t_pos	end = {
		center.x + map->width * fdf->spacing,
		center.y + map->height * fdf->spacing,
	};

	i = 0;
	p.y = center.y;
	while (p.y < end.y)
	{
		p.x = center.x;
		while (p.x < end.x)
		{
			new = rotate(&fdf->axis, p.x, p.y, map->high[i] * fdf->scale);
			fdf->data[i].x = new.x * fdf->zoom + fdf->pos.x;
			fdf->data[i++].y = new.y * fdf->zoom + fdf->pos.y;
			p.x += fdf->spacing;
		}
		p.y += fdf->spacing;
	}
}

void	render_fdf(t_img *img, t_fdf *fdf, t_map *map)
{
	const int			width = map->width;
	const t_drawline	drawline = fdf->drawline;
	unsigned int		color;
	size_t				idx;
	t_pos				p;

	ft_mempset(img->addr, 0, img->width * img->height * img->bpp);
	transform_fdf_points(fdf, map);
	if (width == 1 && map->height == 1)
		return (putpixel(img, fdf->data[0].x, fdf->data[0].y, map->color[0]));
	p.y = 0;
	while (p.y < map->total)
	{
		p.x = -1;
		while (++p.x < width)
		{
			idx = p.y + p.x;
			color = map->color[idx];
			if (p.x + 1 < width)
				drawline(img, fdf->data[idx], fdf->data[idx + 1], color);
			if (p.y + width < map->total)
				drawline(img, fdf->data[idx], fdf->data[idx + width], color);
		}
		p.y += width;
	}
}
