/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:19:53 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/14 09:43:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static inline
void	xiaolinwu_drawline_horizontal(t_image *img, t_point p0, t_point p1,
			unsigned int color)
{
	const int	delta_x = p1.x - p0.x;
	double		m;
	double		y;
	double		dist;

	if (!delta_x)
		m = 1;
	else
		m = (p1.y - p0.y) / (double) delta_x;
	y = p0.y;
	while (p0.x <= p1.x)
	{
		dist = y - (int) y;
		putpixel(img, p0.x, y, brightness(color, 1 - dist));
		putpixel(img, p0.x++, y + 1, brightness(color, dist));
		y += m;
	}
}

static inline
void	xiaolinwu_drawline_vertical(t_image *img, t_point p0, t_point p1,
			unsigned int color)
{
	const int	delta_y = p1.y - p0.y;
	double		m;
	double		x;
	double		dist;

	if (!delta_y)
		m = 1;
	else
		m = (p1.x - p0.x) / (double) delta_y;
	x = p0.x;
	while (p0.y <= p1.y)
	{
		dist = x - (int) x;
		putpixel(img, x, p0.y, brightness(color, 1 - dist));
		putpixel(img, x + 1, p0.y++, brightness(color, dist));
		x += m;
	}
}

int	xiaolinwu_drawline(t_image *img, t_point p0, t_point p1, unsigned int color)
{
	if (liangbarsky_clipping(&p0, &p1, img->width - 1, img->height - 1) < 0)
		return (-1);
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			xiaolinwu_drawline_horizontal(img, p0, p1, color);
		else
			xiaolinwu_drawline_horizontal(img, p1, p0, color);
	}
	else
	{
		if (p0.y <= p1.y)
			xiaolinwu_drawline_vertical(img, p0, p1, color);
		else
			xiaolinwu_drawline_vertical(img, p1, p0, color);
	}
	return (0);
}
