/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_picture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 15:04:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "parsers.h"

int	parse_picture(const char *path, unsigned int **pic, int *width, int *height)
{
	unsigned char	*img;
	long			total;
	long			i;

	*pic = 0;
	img = stbi_load(path, width, height, 0, RGB);
	if (!img)
		return (ERROR);
	total = *width * *height;
	*pic = malloc(sizeof(unsigned int) * total);
	if (!*pic)
	{
		*width = 0;
		*height = 0;
		return (stbi_image_free(img), ERROR);
	}
	i = -1;
	while (++i < total)
		(*pic)[i] = img[i * 3] << 16 | img[i * 3 + 1] << 8 | img[i * 3 + 2];
	return (stbi_image_free(img), SUCCESS);
}
