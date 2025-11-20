/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:00:27 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 12:11:30 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"
#include <unistd.h>

static inline
void	img_map_error(void)
{
	write(2, "Fail loading image map\n", 23);
}

static inline
void	sky_error(void)
{
	write(2, "Fail loading sky\n", 17);
}

static inline
void	fdf_map_error(void)
{
	write(2, "Fail loading fdf map\n", 21);
}

int	parse_arguments(char **argv, t_map *map, t_pic *sky, int flags)
{
	*map = (t_map){};
	*sky = (t_pic){};
	while (*argv && (flags & DONE) != DONE)
	{
		if (!ft_strcmp(*argv, "--images") && *++argv && *++argv && !(flags & MAP))
		{
			if (parse_voxel_file(*(argv - 1), *argv, map) < 0)
				return (img_map_error(), free_pic(sky, NULL), 0);
			flags |= MAP;
		}
		else if (!ft_strcmp(*argv, "--sky") && *++argv && !(flags & SKY))
		{
			if (parse_picture(*argv, &sky->data, &sky->width, &sky->height) < 0)
				return (sky_error(), free_map(map, NULL), 0);
			flags |= SKY;
		}
		else if (*argv && !(flags & MAP))
		{
			if (parse_fdf_file(*argv, map) < 0)
				return (fdf_map_error(), free_pic(sky, NULL), 0);
			flags |= MAP;
		}
		argv += *argv != 0;
	}
	return (flags);
}
