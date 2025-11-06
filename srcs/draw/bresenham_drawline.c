/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:19:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/06 11:55:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static
void	bresenham_drawline_horizontal(t_image image, t_point p0, t_point p1, unsigned int color)
{
	const t_point	delta = {p1.x - p0.x, p1.y - p0.y};
	const int		dir = 1 - 2 * (delta.y < 0);
	const t_point	inc = {delta.x<<1, (delta.y * dir)<<1};
	int				decision;

	decision = inc.y - delta.x;
	while (p0.x <= p1.x)
	{
		putpixel(image, p0.x++, p0.y, color);
		if (decision >= 0)
		{
			p0.y += dir;
			decision -= inc.x;
		}
		decision += inc.y;
	}
}

static
void	bresenham_drawline_vertical(t_image image, t_point p0, t_point p1, unsigned int color)
{
	const t_point	delta = {p1.x - p0.x, p1.y - p0.y};
	const int		dir = 1 - 2 * (delta.x < 0);
	const t_point	inc = {(delta.x * dir)<<1, delta.y<<1};
	int				decision;

	decision = inc.x - delta.y;
	while (p0.y <= p1.y)
	{
		putpixel(image, p0.x, p0.y++, color);
		if (decision >= 0)
		{
			p0.x += dir;
			decision -= inc.y;
		}
		decision += inc.x;
	}
}

int	bresenham_drawline(t_image image, t_point p0, t_point p1, unsigned int color)
{
	if (liangbarsky_clipping(&p0, &p1, image.width - 1, image.height - 1) < 0)
		return (-1);
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			bresenham_drawline_horizontal(image, p0, p1, color);
		else
			bresenham_drawline_horizontal(image, p1, p0, color);
	}
	else
	{
		if (p0.y <= p1.y)
			bresenham_drawline_vertical(image, p0, p1, color);
		else
			bresenham_drawline_vertical(image, p1, p0, color);
	}
	return (0);
}
