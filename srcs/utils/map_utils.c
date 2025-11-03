/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 10:34:34 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 10:35:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	free_map(t_map *map, void (*free_struct)(void *))
{
	free(map->altitude);
	free(map->color);
	if (free_struct)
		free_struct(map);
}
