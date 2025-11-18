/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:55:51 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 19:17:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	free_map(t_map *map, void (*free_struct)(void *))
{
	free(map->altitude);
	free(map->color);
	*map = (t_map){};
	if (free_struct)
		free_struct(map);
}

