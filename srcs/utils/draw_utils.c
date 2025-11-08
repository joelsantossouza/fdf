/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:23:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/08 16:48:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	putpixel(t_image *image, int x, int y, unsigned color)
{
	*(unsigned *) (image->addr + (image->linelen * y + x * (image->bpp / 8))) = color;
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
