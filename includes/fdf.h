/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 19:27:31 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define ERROR		-1
# define SUCCESS	0
# define DEC_BASE	"0123456789"

# define WHITE		0xFFFFFFFF

typedef struct s_map
{
	unsigned int	width;
	unsigned int	height;
	unsigned long	total;
	unsigned int	*color;	
	int				*altitude;	
}	t_map;

typedef struct s_image
{
	void	*data;
	char	*addr;
	int		bpp;
	int		width;
	int		endian;
}	t_image;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

// UTILS
void			free_map(t_map *map, void (*free_struct)(void *));
void			putpixel(t_image image, unsigned int width, unsigned int height, unsigned int color);
unsigned int	brightness(unsigned int color, double scale);

// PARSING
int		parse_fdf_file(const char *path, t_map *map);

// RENDER
void	bresenham_drawline(t_image image, t_point p0, t_point p1, unsigned int color);
void	xiaolinwu_drawline(t_image image, t_point p0, t_point p1, unsigned int color);

#endif
