/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 10:24:30 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ERROR		-1
# define SUCCESS	0
# define DEC_BASE	"0123456789"

# define WHITE		0xFFFFFF

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	unsigned long	total;
	unsigned int	*color;	
	int				*altitude;	
}	t_map;

void	free_map(t_map *map, void (*free_struct)(void *));
int		parse_fdf_file(const char *path, t_map *map);

#endif
