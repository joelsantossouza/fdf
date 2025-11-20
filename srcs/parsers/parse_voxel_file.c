/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_voxel_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 14:19:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stb_image.h"
#include "fdf.h"
#include "parsers.h"
#include <stdlib.h>

int	parse_voxel_file(const char *color_file, const char *height_file,
		t_map *map)
{
	unsigned char	*color;
	unsigned char	*high;
	t_pos			size;
	long			i;

	color = stbi_load(color_file, &size.x, &size.y, 0, RGB);
	high = stbi_load(height_file, &map->width, &map->height, 0, GRAYSCALE);
	if (!color || !high || map->width != size.x || map->height != size.y)
		return (*map = (t_map){}, stbi_image_free(color),
			stbi_image_free(high), ERROR);
	map->total = map->width * map->height;
	map->color = malloc(sizeof(*map->color) * map->total);
	map->high = malloc(sizeof(*map->high) * map->total);
	if (!map->color || !map->high)
		return (free_map(map, NULL), stbi_image_free(color),
			stbi_image_free(high), ERROR);
	i = -1;
	while (++i < map->total)
	{
		map->color[i] = color[i * 3] << 16 | color[i * 3 + 1] << 8
			| color[i * 3 + 2];
		map->high[i] = high[i];
	}
	return (stbi_image_free(color), stbi_image_free(high), SUCCESS);
}
