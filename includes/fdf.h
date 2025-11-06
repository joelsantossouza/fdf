/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/05 23:59:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>

# define ERROR		-1
# define SUCCESS	0
# define DEC_BASE	"0123456789"

# define WHITE		0xFFFFFFFF

typedef struct s_map
{
	int				width;
	int				height;
	long			total;
	unsigned int	*color;	
	int				*altitude;	
}	t_map;

typedef struct s_image
{
	void	*data;
	char	*addr;
	int		bpp;
	int		linelen;
	int		width;
	int		height;
}	t_image;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_rotation
{
	double	x;
	double	y;
	double	z;
}	t_rotation;

typedef struct s_fdf
{
	t_map		*map;
	t_point		position;
	t_point		*transformed;
	t_rotation	rotation;
	double		zoom;
	int			spacing;
}	t_fdf;

typedef int (t_linedrawer)(t_image, t_point, t_point, unsigned int);

// UTILS
void			free_map(t_map *map, void (*free_struct)(void *));
void	putpixel(t_image image, int x, int y, unsigned int color);
unsigned int	brightness(unsigned int color, double scale);

// PARSING
int		parse_fdf_file(const char *path, t_map *map);

// DRAW
int	liangbarsky_clipping(t_point *p0, t_point *p1, int width, int height);
int	bresenham_drawline(t_image image, t_point p0, t_point p1, unsigned int color);
int	xiaolinwu_drawline(t_image image, t_point p0, t_point p1, unsigned int color);

// RENDER
void	render_fdf(t_image image, t_fdf fdf, t_linedrawer *drawline);

#endif
