/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_voxel_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 13:31:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stb_image.h"
#include "libft.h"
#include "fdf.h"
#include "parsers.h"
#include <stdlib.h>

int	parse_voxel_file(const char *color_file, const char *height_file, t_map *map, int heightscale)
{
	t_point			size;
	unsigned char	*color;
	unsigned char	*height;
	long			i;

	color = stbi_load(color_file, &size.x, &size.y, 0, RGB);
	height = stbi_load(height_file, &map->width, &map->height, 0, GRAYSCALE);
	if (!color || !height || map->width != size.x || map->height != size.y)
		return (ft_bzero(map, sizeof(*map)), stbi_image_free(color), stbi_image_free(height), ERROR);
	map->total = map->width * map->height;
	map->color = malloc(sizeof(*map->color) * map->total);
	map->altitude = malloc(sizeof(*map->altitude) * map->total);
	if (!map->color || !map->altitude)
	{
		free_map(map, NULL);
		return (ft_bzero(map, sizeof(*map)), stbi_image_free(color), stbi_image_free(height), ERROR);
	}
	i = -1;
	while (++i < map->total)
	{
		map->color[i] = color[i * 3] << 16 | color[i * 3 + 1] << 8 | color[i * 3 + 2];
		map->altitude[i] = height[i] * heightscale;
	}
	return (stbi_image_free(color), stbi_image_free(height), SUCCESS);
}
