/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 18:04:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/02 16:35:16 by joesanto         ###   ########.fr       */
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
	const int	file = open(path, O_RDONLY);
	char		*line;

	line = NULL;
	get_next_line(&line, file);
	map->width = ft_word_count(line, ' ');
	if (!map->width || get_next_line(&line, file) < 0)
		return (close(file), ft_bzero(map, sizeof(*map)), ERROR);
	map->height = 1;
	while (line)
	{
		if (ft_word_count(line, ' ') != map->width || get_next_line(&line, file) < 0)
			return (close(file), ft_bzero(map, sizeof(*map)), free(line), ERROR);
		map->height++;
	}
	map->total = map->width * map->height;
	map->altitude = malloc(sizeof(*map->altitude) * map->total);
	map->color = malloc(sizeof(*map->color) * map->total);
	if (!map->altitude || !map->color)
	{
		free_map(map, NULL);
		return (close(file), ft_bzero(map, sizeof(*map)), ERROR);
	}
	return (close(file), SUCCESS);
}

int	parse_fdf_file(const char *path, t_map *map)
{
	const int	file = open(path, O_RDONLY);
	char		**split;
	char		*line;
	size_t		i;

	line = NULL;
	if (validate_map(path, map) < 0 || get_next_line(&line, file) < 0)
		return (close(file), free_map(map, NULL), ERROR);
	i = -1;
	while (line)
	{
		ptr = line;
		width = map->width;
		while (width--)
		{
			map->altitude[++i] = ft_atol_base(ptr, &ptr, DEC_BASE);
			if (*ptr++ == ',')
				map->color[i] = ft_atoh(ptr, &ptr);
			else
				map->color[i] = WHITE;
		}
		if (get_next_line(&line, file) < 0)
			return (close(file), free_map(map, NULL), ERROR);
	}
	return (close(file), SUCCESS);
}
