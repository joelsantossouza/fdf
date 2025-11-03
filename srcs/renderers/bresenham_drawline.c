/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:19:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 23:07:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

static
void	bresenham_drawline_horizontal(t_image image, t_pixel p0, t_pixel p1)
{
	t_pixel	delta;
	int		direction;
	int		decision;

	delta = (t_pixel) {.x = p1.x - p0.x, .y = p1.y - p0.y};
	direction = 1;
	if (delta.y < 0)
	{
		direction = -1;
		delta.y *= -1;
	}
	decision = 2 * delta.y - delta.x;
	while (p0.x <= p1.x)
	{
		putpixel(image, p0.x++, p0.y, 0xFFFFFF);
		if (decision >= 0)
		{
			p0.y += direction;
			decision -= 2 * delta.x;
		}
		decision += 2 * delta.y;
	}
}

static
void	bresenham_drawline_vertical(t_image image, t_pixel p0, t_pixel p1)
{
	t_pixel	delta;
	int		direction;
	int		decision;

	delta = (t_pixel) {.x = p1.x - p0.x, .y = p1.y - p0.y};
	direction = 1;
	if (delta.x < 0)
	{
		direction = -1;
		delta.x *= -1;
	}
	decision = 2 * delta.x - delta.y;
	while (p0.y <= p1.y)
	{
		putpixel(image, p0.x, p0.y++, 0xFFFFFF);
		if (decision >= 0)
		{
			p0.x += direction;
			decision -= 2 * delta.y;
		}
		decision += 2 * delta.x;
	}
}

void	bresenham_drawline(t_image image, t_pixel p0, t_pixel p1)
{
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			bresenham_drawline_horizontal(image, p0, p1);
		else
			bresenham_drawline_horizontal(image, p1, p0);
	}
	else
	{
		if (p0.y <= p1.y)
			bresenham_drawline_vertical(image, p0, p1);
		else
			bresenham_drawline_vertical(image, p1, p0);
	}
}
