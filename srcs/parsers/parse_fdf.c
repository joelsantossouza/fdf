/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/05 12:23:06 by joesanto         ###   ########.fr       */
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
		if (ft_word_count(line, ' ') != (size_t) map->width || ft_getline(&line, fd) < 0)
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
	char	*file;
	char	*ptr;
	long	i;

	file = NULL;
	if (validate_map(path, map) < 0 || ft_getfile(&file, path) < 0)
		return (free_map(map, NULL), ERROR);
	i = -1;
	ptr = file;
	while (++i < map->total)
	{
		map->altitude[i] = ft_atol_base(ptr, &ptr, DEC_BASE);
		if (*ptr == ',')
			map->color[i] = ft_atoh(++ptr, &ptr);
		else
			map->color[i] = WHITE;
		ptr = ft_strpbrknul(ptr, " \n");
	}
	return (free(file), SUCCESS);
}
