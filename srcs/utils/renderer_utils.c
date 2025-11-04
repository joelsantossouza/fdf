/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:23:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 18:24:51 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	putpixel(t_image image, unsigned int width, unsigned int height, unsigned int color)
{
	*(unsigned int *) (image.addr + (image.width * height + width * (image.bpp / 8))) = color;
}

unsigned int	brightness(t_color color, double scale)
{
	if (scale < 0)
		scale = 0;
	else if (scale > 1)
		scale = 1;
	color.r *= scale;
	color.g *= scale;
	color.b *= scale;
	return (((int)color.r << 16) | ((int)color.g << 8) | (int)color.b);
}
