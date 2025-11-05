/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/05 19:11:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static inline
void	render_fdf_horizontal_lines(t_image image, t_map map, t_fdf fdf, t_linedrawer *drawline)
{
	t_point			p;
	const int		start_x = fdf.position.x + fdf.spacing;
	const t_point	end = (t_point){
		fdf.position.x + map.width * fdf.spacing,
		fdf.position.y + map.height * fdf.spacing,
	};

	p.y = fdf.position.y;
	while (p.y < end.y)
	{
		p.x = start_x;
		while (p.x < end.x)
		{
			drawline(image, (t_point){p.x - fdf.spacing, p.y}, p, WHITE);
			p.x += fdf.spacing;
		}
		p.y += fdf.spacing;
	}
}

static inline
void	render_fdf_vertical_lines(t_image image, t_map map, t_fdf fdf, t_linedrawer *drawline)
{
	t_point			p;
	const int		start_y = fdf.position.y + fdf.spacing;
	const t_point	end = (t_point){
		fdf.position.x + map.width * fdf.spacing,
		fdf.position.y + map.height * fdf.spacing,
	};

	p.x = fdf.position.x;
	while (p.x < end.x)
	{
		p.y = start_y;
		while (p.y < end.y)
		{
			drawline(image, (t_point){p.x, p.y - fdf.spacing}, p, WHITE);
			p.y += fdf.spacing;
		}
		p.x += fdf.spacing;
	}
}

void	render_fdf(t_image image, t_map map, t_fdf fdf, t_linedrawer *drawline)
{
	if (map.width == 1 && map.height == 1)
		return (putpixel(image, fdf.position.x, fdf.position.y, WHITE));
	render_fdf_horizontal_lines(image, map, fdf, drawline);
	render_fdf_vertical_lines(image, map, fdf, drawline);
}
