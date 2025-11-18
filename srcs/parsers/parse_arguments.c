/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:00:27 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 17:38:35 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"

int	parse_arguments(char **argv, t_map *map, t_pic *sky, int flags)
{
	ft_mempset(map, 0, sizeof(*map));
	ft_mempset(sky, 0, sizeof(*sky));
	while (*++argv && (flags & DONE) != DONE)
	{
		if (!(flags & MAP_DONE) && !ft_strcmp(*argv, "--images") && *(argv + 1) && *(argv + 2))
		{
			if (parse_voxel_file(*(argv + 1), *(argv + 2), map) < 0)
				return (free_pic(sky, NULL), 0);
			flags |= MAP_DONE;
			argv += 2;
		}
		else if (!(flags & SKY_DONE) && !ft_strcmp(*argv, "--sky") && *(argv + 1))
		{
			if (parse_picture(*++argv, &sky->data, &sky->width, &sky->height) < 0)
				return (free_map(map, NULL), 0);
			flags |= SKY_DONE;
		}
		else if (!(flags & MAP_DONE))
		{
			if (parse_fdf_file(*argv, map) < 0)
				return (free_pic(sky, NULL), 0);
			flags |= MAP_DONE;
		}
	}
	return (flags);
}
