/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_picture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/13 09:39:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stb_image.h"
#include "fdf.h"

#define RGB	3

int	parse_picture(const char *path, unsigned int **pic, int *width, int *height)
{
	unsigned char	*color;
	long			total;
	long			i;

	*pic = 0;
	color = stbi_load(path, width, height, 0, RGB);
	if (!color)
		return (ERROR);
	total = *width * *height;
	*pic = malloc(sizeof(unsigned int) * total);
	if (!*pic)
	{
		*width = 0;
		*height = 0;
		return (stbi_image_free(color), ERROR);
	}
	i = -1;
	while (++i < total)
		(*pic)[i] = color[i * 3] << 16 | color[i * 3 + 1] << 8 | color[i * 3 + 2];
	return (stbi_image_free(color), SUCCESS);
}
