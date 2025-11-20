/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 15:00:27 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/20 22:42:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "voxelspace.h"
#include "parsers.h"
#include <unistd.h>

static inline
int	img_map_error(void)
{
	return (write(2, "Fail loading image map\n", 23));
}

static inline
int	sky_error(void)
{
	return (write(2, "Fail loading sky\n", 17));
}

static inline
int	fdf_map_error(void)
{
	return (write(2, "Fail loading fdf map\n", 21));
}

int	parse_arguments(char **arr, t_map *map, t_pic *sky, int flags)
{
	*map = (t_map){};
	*sky = (t_pic){};
	while (*arr && (flags & DONE) != DONE)
	{
		if (!ft_strcmp(*arr, "--images") && *++arr && *++arr && !(flags & MAP))
		{
			if (parse_voxel_file(*(arr - 1), *arr, map) < 0)
				return (img_map_error(), free_pic(sky, NULL), 0);
			flags |= MAP;
		}
		else if (!ft_strcmp(*arr, "--sky") && *++arr && !(flags & SKY))
		{
			if (parse_picture(*arr, &sky->data, &sky->width, &sky->height) < 0)
				return (sky_error(), free_map(map, NULL), 0);
			flags |= SKY;
		}
		else if (*arr && !(flags & MAP))
		{
			if (parse_fdf_file(*arr, map) < 0)
				return (fdf_map_error(), free_pic(sky, NULL), 0);
			flags |= MAP;
		}
		arr += *arr != 0;
	}
	return (flags);
}
