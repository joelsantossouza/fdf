/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:19:53 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 14:25:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

#                    	define COLOR 0x1152ff
static
void	xiaolinwu_drawline_horizontal(t_image image, t_pixel p0, t_pixel p1)
{
	const t_pixel	delta = (t_pixel) {.x = p1.x - p0.x, .y = p1.y - p0.y};
	const double	m = delta.y / (double) (delta.x + (delta.x == 0) * delta.y);
	double			y;
	double			dist;

	y = p0.y;
	while (p0.x <= p1.x)
	{
		dist = y - (int) y;
		putpixel(image, p0.x, y, transparency(COLOR, dist));
		putpixel(image, p0.x++, y + 1, transparency(COLOR, 1 - dist));
		y += m;
	}
}

static
void	xiaolinwu_drawline_vertical(t_image image, t_pixel p0, t_pixel p1)
{
	const t_pixel	delta = (t_pixel) {.x = p1.x - p0.x, .y = p1.y - p0.y};
	const double	m = delta.x / (double) (delta.y + (delta.y == 0) * delta.x);
	double			x;
	double			dist;

	x = p0.x;
	while (p0.y <= p1.y)
	{
		dist = x - (int) x;
		putpixel(image, x, p0.y, transparency(COLOR, dist));
		putpixel(image, x + 1, p0.y++, transparency(COLOR, 1 - dist));
		x += m;
	}
}

void	xiaolinwu_drawline(t_image image, t_pixel p0, t_pixel p1)
{
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			xiaolinwu_drawline_horizontal(image, p0, p1);
		else
			xiaolinwu_drawline_horizontal(image, p1, p0);
	}
	else
	{
		if (p0.y <= p1.y)
			xiaolinwu_drawline_vertical(image, p0, p1);
		else
			xiaolinwu_drawline_vertical(image, p1, p0);
	}
}
