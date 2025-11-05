/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/05 18:04:43 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_fdf(t_image image, t_map map, t_fdf fdf, t_linedrawer *drawline)
{
	const t_point	end = (t_point){
		fdf.position.x + map.width * fdf.spacing,
		fdf.position.y + map.height * fdf.spacing,
	};
	t_point			p;

	if (map.width == 1 && map.height == 1)
		putpixel(image, fdf.position.x, fdf.position.y, WHITE);
	p.y = fdf.position.y;
	while (p.y < end.y)
	{
		p.x = fdf.position.x;
		while (p.x < end.x)
		{
			if (p.y + fdf.spacing < end.y)
				drawline(image, p, (t_point){p.x, p.y + fdf.spacing}, WHITE);
			if (p.x + fdf.spacing < end.x)
				drawline(image, p, (t_point){p.x + fdf.spacing, p.y}, WHITE);
			p.x += fdf.spacing;
		}
		p.y += fdf.spacing;
	}
}
