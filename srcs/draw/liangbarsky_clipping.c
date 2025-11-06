/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liangbarsky_clipping.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 13:55:37 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/06 11:56:38 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

int	liangbarsky_clipping(t_point *p0, t_point *p1, int width, int height)
{
	const t_point	delta = {p1->x - p0->x, p1->y - p0->y};
	const int		p[4] = {-(delta.x), delta.x, -delta.y, delta.y};
	const int		q[4] = {p0->x, width - p0->x, p0->y, height - p0->y};
	double			t[2];
	int				i;

	t[0] = 0.0;
	t[1] = 1.0;
	i = -1;
	while (++i < 4)
	{
		if (p[i] == 0 && q[i] < 0)
			return (-1);
		else if (p[i] < 0)
			t[0] = fmax(t[0], q[i] / (double) p[i]);
		else if (p[i] > 0)
			t[1] = fmin(t[1], q[i] / (double) p[i]);
	}
	if (t[0] > t[1])
		return (-1);
	p1->x = round(p0->x + delta.x * t[1]);
	p1->y = round(p0->y + delta.y * t[1]);
	p0->x = round(p0->x + delta.x * t[0]);
	p0->y = round(p0->y + delta.y * t[0]);
	return (0);
}
