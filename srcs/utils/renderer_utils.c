/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 18:23:01 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 18:27:30 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	putpixel(t_image image, unsigned int width, unsigned int height, unsigned int color)
{
	*(unsigned int *) (image.addr + (image.width * height + width * (image.bpp / 8))) = color;
}
