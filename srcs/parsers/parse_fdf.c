/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/02 18:23:39 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	free_map(t_map *map, void (*free_struct)(void *))
{
	free(map->altitude);
	free(map->color);
	if (free_struct)
		free_struct(map);
}

static
int	validate_map(const char *path, t_map *map)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;

	line = NULL;
	ft_getline(&line, fd);
	map->width = ft_word_count(line, ' ');
	if (!map->width || ft_getline(&line, fd) < 0)
		return (close(fd), ft_bzero(map, sizeof(*map)), ERROR);
	map->height = 1;
	while (line)
	{
		if (ft_word_count(line, ' ') != map->width || ft_getline(&line, fd) < 0)
			return (close(fd), ft_bzero(map, sizeof(*map)), free(line), ERROR);
		map->height++;
	}
	map->total = map->width * map->height;
	map->altitude = malloc(sizeof(*map->altitude) * map->total);
	map->color = malloc(sizeof(*map->color) * map->total);
	if (!map->altitude || !map->color)
	{
		free_map(map, NULL);
		return (close(fd), ft_bzero(map, sizeof(*map)), ERROR);
	}
	return (close(fd), SUCCESS);
}

int	parse_fdf_file(const char *path, t_map *map)
{
	const int	fd = open(path, O_RDONLY);
	char		**data;
	char		*line;
	unsigned int	i;
	unsigned int	j;

	if (fd < 0 || validate_map(path, map) < 0)
		return (close(fd), ERROR);
	j = -1;
	line = NULL;
	while (++j < map->height)
	{
		i = -1;
		ft_getline(&line, fd);
		data = ft_split(line, ' ');
		if (!data)
			return (close(fd), free_map(map, NULL), free(line), ERROR);
		while (++i < map->width)
		{
			map->altitude[map->width * j + i] = ft_atol_base(data[i], NULL, DEC);
			if (*ptr++ == ',')
				map->color[i] = ft_atoh(ptr, &ptr);
			else
				map->color[i] = WHITE;
		}
	}
	return (close(fd), SUCCESS);
}
