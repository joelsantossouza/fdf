/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 01:07:08 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/13 09:27:34 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdlib.h>
#include "voxelspace.h"

void	print_map(t_map map)
{
	int	i;
	int	j;

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

	map = malloc(sizeof(t_map));
	if (!map)
		return (2);
	returnval = ERROR;
	if (argc == 2)
		returnval = parse_fdf_file(argv[1], map);
	else if (argc == 3)
		returnval = parse_voxel_file(argv[1], argv[2], map, 1);
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
