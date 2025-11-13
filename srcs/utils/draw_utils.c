/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:23:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/13 12:04:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include <math.h>

void	putpixel(t_image *img, int x, int y, unsigned color)
{
	*(unsigned *) (img->addr + (img->linelen * y + x * (img->bpp / 8))) = color;
}

unsigned	brightness(unsigned color, double scale)
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;

	if (scale < 0)
		scale = 0;
	else if (scale > 1)
		scale = 1;
	red = ((color & 0x00ff0000) >> 16) * scale;
	green = ((color & 0x0000ff00) >> 8) * scale;
	blue = (color & 0x000000ff) * scale;
	return ((red << 16) | (green << 8) | blue);
}

unsigned int	sky_sphere(t_pic *sky, double h_angle, double v_angle)
{
	const int	width = sky->width;
	const int	height = sky->height;
	int	x;
	int	y;

	h_angle = fmod(h_angle + CIRCLE, CIRCLE);
	x = (int)(h_angle / CIRCLE * width);
	y = (int)(((v_angle + QUADRANT) / PI) * height);
	if (y < 0)
		y = 0;
	else if (y >= height)
		y = height - 1;
	return (sky->data[width * y + x]);
}
