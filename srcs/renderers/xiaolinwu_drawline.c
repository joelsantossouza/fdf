/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:19:53 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 18:26:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static
void	xiaolinwu_drawline_horizontal(t_image image, t_pixel p0, t_pixel p1)
{
	const double	delta_x = p1.x - p0.x;
	t_color			inc;
	double			m;
	double			y;
	double			dist;

	if (!delta_x)
		m = 0;
	else
		m = (p1.y - p0.y) /  delta_x;
	inc.r = (p1.color.r - p0.color.r) / delta_x;
	inc.g = (p1.color.g - p0.color.g) / delta_x;
	inc.b = (p1.color.b - p0.color.b) / delta_x;
	y = p0.y;
	while (p0.x <= p1.x)
	{
		dist = y - (int) y;
		putpixel(image, p0.x, y, brightness(p0.color, 1 - dist));
		putpixel(image, p0.x++, y + 1, brightness(p0.color, dist));
		p0.color.r += inc.r;
		p0.color.g += inc.g;
		p0.color.b += inc.b;
		y += m;
	}
}

static
void	xiaolinwu_drawline_vertical(t_image image, t_pixel p0, t_pixel p1)
{
	const int	delta_y = p1.y - p0.y;
	t_color		inc;
	double		m;
	double		x;
	double		dist;

	if (!delta_y)
		m = 0;
	else
		m = (p1.x - p0.x) / (double) delta_y;
	inc.r = (p1.color.r - p0.color.r) / delta_y;
	inc.g = (p1.color.g - p0.color.g) / delta_y;
	inc.b = (p1.color.b - p0.color.b) / delta_y;
	x = p0.x;
	while (p0.y <= p1.y)
	{
		dist = x - (int) x;
		putpixel(image, x, p0.y, brightness(p0.color, 1 - dist));
		putpixel(image, x + 1, p0.y++, brightness(p0.color, dist));
		p0.color.r += inc.r;
		p0.color.g += inc.g;
		p0.color.b += inc.b;
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
