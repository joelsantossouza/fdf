/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 18:29:05 by joesanto         ###   ########.fr       */
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

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_pixel
{
	unsigned int	x;
	unsigned int	y;
	t_color			color;
}	t_pixel;

// UTILS
void			free_map(t_map *map, void (*free_struct)(void *));
void			putpixel(t_image image, unsigned int width, unsigned int height, unsigned int color);
unsigned int	brightness(t_color color, double scale);

// PARSING
int		parse_fdf_file(const char *path, t_map *map);

// RENDER
void	bresenham_drawline(t_image image, t_pixel p0, t_pixel p1);
void	xiaolinwu_drawline(t_image image, t_pixel p0, t_pixel p1);

#endif
