/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:55:51 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 16:39:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	free_map(t_map *map, void (*free_struct)(void *))
{
	free(map->altitude);
	free(map->color);
	map->width = 0;
	map->height = 0;
	map->total = 0;
	map->altitude = 0;
	map->color = 0;
	if (free_struct)
		free_struct(map);
}

