/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:19:53 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 19:31:48 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static
void	xiaolinwu_drawline_horizontal(t_image image, t_point p0, t_point p1, unsigned int color)
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
		putpixel(image, p0.x, y, brightness(color, 1 - dist));
		putpixel(image, p0.x++, y + 1, brightness(color, dist));
		y += m;
	}
}

static
void	xiaolinwu_drawline_vertical(t_image image, t_point p0, t_point p1, unsigned int color)
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
		putpixel(image, x, p0.y, brightness(color, 1 - dist));
		putpixel(image, x + 1, p0.y++, brightness(color, dist));
		x += m;
	}
}

void	xiaolinwu_drawline(t_image image, t_point p0, t_point p1, unsigned int color)
{
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			xiaolinwu_drawline_horizontal(image, p0, p1, color);
		else
			xiaolinwu_drawline_horizontal(image, p1, p0, color);
	}
	else
	{
		if (p0.y <= p1.y)
			xiaolinwu_drawline_vertical(image, p0, p1, color);
		else
			xiaolinwu_drawline_vertical(image, p1, p0, color);
	}
}
