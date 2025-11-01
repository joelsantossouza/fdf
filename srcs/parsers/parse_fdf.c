/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/01 20:54:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static
int	validate_map(const char *path, t_map *map)
{
	const int	file = open(path, O_RDONLY);
	char		*line;

	line = 0;
	get_next_line(&line, file);
	map->width = ft_word_count(line, ' ');
	if (!map->width)
		return (close(file), ERROR);
	map->height = 1;
	while (line)
	{
		get_next_line(&line, file);
		if (ft_word_count(line, ' ') != map->width)
			return (close(file), free(line), ERROR);
		map->height++;
	}
	map->total = map->width * map->height;
	map->altitude = malloc(sizeof(*map->altitude) * map->total);
	if (!map->altitude)
		return (close(file), ERROR);
	map->color = malloc(sizeof(*map->color) * map->total);
	if (!map->color)
		return (close(file), free(map->altitude), ERROR);
	return (close(file), SUCCESS);
}

t_map	*parse_fdf_file(const char *path)
{
	const int	file = open(path, O_RDONLY);
	size_t		i;
	t_map		*map;
	char		*line;
	char		*ptr;

	line = 0;
	map = malloc(sizeof(t_map));
	if (!map || validate_map(path, map) < 0 || get_next_line(&line, file) < 0)
		return (close(file), free(map), NULL);
	i = -1;
	while (line)
	{
		ptr = line;
		while (++i + 1 % map->width != 0)
		{
			map->altitude[i] = ft_atol_base(ptr, &ptr, DEC_BASE);
			if (*ptr++ == ',')
				map->color[i] = ft_atoh(ptr, &ptr);
		}
		if (get_next_line(&line, file) < 0)
			return (close(file), free(map), NULL);
	}
	return (close(file), map);
}
