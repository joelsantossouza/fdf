/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 21:29:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "parsers.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static
int	validate_map(const char *path, t_map *map)
{
	const int	fd = open(path, O_RDONLY);
	char		*line;

	if (fd < 0)
		return (ERROR);
	line = NULL;
	ft_getline(&line, fd);
	map->width = ft_word_count(line, ' ');
	if (!map->width || ft_getline(&line, fd) < 0)
		return (close(fd), *map = (t_map){}, ERROR);
	map->height = 1;
	while (line)
	{
		if (ft_word_count(line, ' ') != (size_t)map->width
			|| ft_getline(&line, fd) < 0)
			return (close(fd), *map = (t_map){}, free(line), ERROR);
		map->height++;
	}
	map->total = map->width * map->height;
	map->high = malloc(sizeof(*map->high) * map->total);
	map->color = malloc(sizeof(*map->color) * map->total);
	if (!map->high || !map->color)
		return (close(fd), free_map(map, NULL), ERROR);
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
		map->high[i] = ft_atol_base(ptr, &ptr, DEC_BASE);
		if (*ptr == ',')
			map->color[i] = ft_atoh(++ptr, &ptr);
		else
			map->color[i] = WHITE;
		ptr = ft_strpbrknul(ptr, " \n");
	}
	return (free(file), SUCCESS);
}
