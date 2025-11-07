/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_voxel_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/07 18:51:54 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "libft.h"
#include "fdf.h"
#include <stdlib.h>

#define RGB			3
#define	GRAYSCALE	1

int	parse_voxel_file(const char *color_file, const char *altitude_file, t_map *map)
{
	t_point			dimension;
	unsigned char	*color;
	unsigned char	*altitude;
	long			i;

	color = stbi_load(color_file, &dimension.x, &dimension.y, 0, RGB);
	altitude = stbi_load(altitude_file, &map->width, &map->height, 0, GRAYSCALE);
	if (!color || !altitude || map->width != dimension.x || map->height != dimension.y)
		return (ft_bzero(map, sizeof(*map)), free(color), free(altitude), ERROR);
	map->total = map->width * map->height;
	map->color = malloc(sizeof(*map->color) * map->total);
	map->altitude = malloc(sizeof(*map->altitude) * map->total);
	if (!map->color || !map->altitude)
	{
		free_map(map, NULL);
		return (ft_bzero(map, sizeof(*map)), free(color), free(altitude), ERROR);
	}
	i = -1;
	while (++i < map->total)
	{
		map->color[i] = *(unsigned int *)(color + (i * RGB));
		map->altitude[i] = *(unsigned int *)(altitude + i);
	}
	return (stbi_image_free(color), stbi_image_free(altitude), SUCCESS);
}
