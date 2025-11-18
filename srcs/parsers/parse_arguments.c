/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:00:27 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 15:43:02 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"

int	parse_arguments(char **argv, t_map *map, t_pic *sky)
{
	int			flags;

	flags = 0;
	while (*++argv && (flags & DONE) != DONE)
	{
		if (!(flags & MAP_DONE) && !ft_strcmp(*argv, "--images") && *(argv + 1) && *(argv + 2))
		{
			if (parse_voxel_file(*++argv, *++argv, map) < 0)
				return (free_pic(sky), ERROR);
			flags |= MAP_DONE;
		}
		else if (!(flags & SKY_DONE) && !ft_strcmp(*argv, "--sky") && *(argv + 1))
		{
			if (parse_picture(*++argv, &sky->data, &sky->width, &sky->height) < 0)
				return (free_map(map, NULL), ERROR);
			flags |= SKY_DONE;
		}
		else if (!(flags & MAP_DONE))
		{
			if (parse_fdf_file(*argv, map) < 0)
				return (free_pic(sky), ERROR);
			flags |= MAP_DONE;
		}
	}
	return (SUCCESS);
}
