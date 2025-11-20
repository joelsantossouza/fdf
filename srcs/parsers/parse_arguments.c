/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:00:27 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 10:52:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"
#include <unistd.h>

static inline
void	map_error(void)
{
	write(2, "Fail loading map\n", 17);
}

static inline
void	sky_error(void)
{
	write(2, "Fail loading sky\n", 17);
}

int	parse_arguments(char **argv, t_map *map, t_pic *sky, int flags)
{
	*map = (t_map){};
	*sky = (t_pic){};
	while (*++argv && (flags & DONE) != DONE)
	{
		if (!(flags & MAP_DONE) && !ft_strcmp(*argv, "--images") && *(argv + 1) && *(argv + 2))
		{
			if (parse_voxel_file(*(argv + 1), *(argv + 2), map) < 0)
				return (map_error(), free_pic(sky, NULL), 0);
			flags |= MAP_DONE;
			argv += 2;
		}
		else if (!(flags & SKY_DONE) && !ft_strcmp(*argv, "--sky") && *(argv + 1))
		{
			if (parse_picture(*++argv, &sky->data, &sky->width, &sky->height) < 0)
				return (sky_error(), free_map(map, NULL), 0);
			flags |= SKY_DONE;
		}
		else if (!(flags & MAP_DONE))
		{
			if (parse_fdf_file(*argv, map) < 0)
				return (map_error(), free_pic(sky, NULL), 0);
			flags |= MAP_DONE;
		}
	}
	return (flags);
}
