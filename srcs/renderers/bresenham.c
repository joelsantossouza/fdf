/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:19:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 17:42:19 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static
void	bresenham_drawline_horizontal(t_image image, t_pixel p0, t_pixel p1)
{
	t_point	delta;
	int		direction;
	int		decision;

	if (p0.x > p1.x)
		ft_swap(&p0, &p1, sizeof(t_pixel));
	delta = (t_point) {.x = p1.x - p0.x, .y = p1.y - p0.y};
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
