/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fdf_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 01:07:08 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 10:03:05 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>

void	print_map(t_map map)
{
	unsigned int	i;
	unsigned int	j;

	ft_printf("-- Color Map --\n");
	j = -1;
	while (++j < map.height)
	{
		i = -1;
		while (++i < map.width)
			ft_printf("%3u ", map.color[map.width * j + i]);
		ft_printf("\n");
	}
	ft_printf("\n");
	ft_printf("-- Altitude Map --\n");
	j = -1;
	while (++j < map.height)
	{
		i = -1;
		while (++i < map.width)
			ft_printf("%3d ", map.altitude[map.width * j + i]);
		ft_printf("\n");
	}
	ft_printf("\n");
}

int	main(int argc, char **argv)
{
	t_map	*map;
	int		returnval;

	if (argc != 2)
	{
		ft_fprintf(2, "Usage: %s <map>\n", *argv);
		return (1);
	}
	map = malloc(sizeof(t_map));
	if (!map)
		return (2);
	returnval = ERROR;
	if (ft_strstr(argv[1], ".fdf"))
		returnval = parse_fdf_file(argv[1], map);
	//else if (ft_strstr(argv[1], ".fdf") == 0)
	//	parse_gif_file()
	if (returnval != ERROR)
	{
		ft_printf("map->width: %u\n", map->width);
		ft_printf("map->height: %u\n", map->height);
		ft_printf("map->total: %u\n", map->total);
		print_map(*map);
	}
	free_map(map, free);
	return (0);
}
