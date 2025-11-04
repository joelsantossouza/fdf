/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:23:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 14:19:15 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	putpixel(t_image image, unsigned int width, unsigned int height, unsigned int color)
{
	*(unsigned int *) (image.addr + (image.width * height + width * (image.bpp / 8))) = color;
}

unsigned int	transparency(unsigned int color, double scale)
{
	unsigned char	t;

	if (scale >= 1)
		t = 0xff;
	else if (scale <= 0)
		t = 0;
	else
		t = 0xff * scale;
	return ((color & 0x00ffffff) | (t << 24));
}
