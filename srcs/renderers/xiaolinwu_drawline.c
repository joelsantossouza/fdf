/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xiaolinwu_drawline.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 09:19:53 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 10:02:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static
void	xiaolinwu_drawline_horizontal(t_image image, t_pixel p0, t_pixel p1)
{
	const t_pixel	delta = (t_pixel) {.x = p1.x - p0.x, .y = p1.y - p0.x};
	const double	m = delta.y / (double) (delta.x + (delta.x == 0) * delta.y);
	double			y;
	double			dist;

	y = p0.y;
	while (p0.x <= p1.x)
	{
		dist = y - (int) y;
		putpixel(image, p0.x, y, 0xffffffff);
		putpixel(image, p0.x++, y + 1, 0xffffffff);
		y += m;
	}
}
