/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:23:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 12:21:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	putpixel(t_image image, unsigned int width, unsigned int height, unsigned int color)
{
	*(unsigned int *) (image.addr + (image.width * height + width * (image.bpp / 8))) = color;
}

unsigned int	transparency(unsigned int color, double scale)
{
	const int		result = ((color >> 24) & 0xff) * scale;
	unsigned char	t;

	if (result < 0)
		t = 0;
	else if (result > 0xff)
		t = 0xff;
	else
		t = result;
	return ((color & 0x00ffffff) | (t < 24));
}
