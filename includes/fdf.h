/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 00:18:11 by joesanto         ###   ########.fr       */
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
	int			width;
	int			height;
	long		total;
	unsigned	*color;	
	int			*altitude;	
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

typedef struct s_angle
{
	double	x;
	double	y;
	double	z;
}	t_angle;

typedef struct s_trig
{
	t_angle	sine;
	t_angle	cosine;
}	t_trig;

typedef struct s_fdf
{
	t_map		*map;
	t_point		center;
	t_point		position;
	t_point		*transformed;
	t_angle		angle;
	t_trig		trig;
	int			spacing;
}	t_fdf;

typedef int (t_linedrawer)(t_image *, t_point, t_point, unsigned int);

// UTILS
void		free_map(t_map *map, void (*free_struct)(void *));
void		putpixel(t_image *image, int x, int y, unsigned color);
unsigned	brightness(unsigned color, double scale);

// PARSING
int			parse_fdf_file(const char *path, t_map *map);
int			parse_voxel_file(const char *color_file, const char *altitude_file, t_map *map);

// DRAW
int	liangbarsky_clipping(t_point *p0, t_point *p1, int width, int height);
int	bresenham_drawline(t_image *image, t_point p0, t_point p1, unsigned color);
int	xiaolinwu_drawline(t_image *image, t_point p0, t_point p1, unsigned color);

// TRANSFORMATION
t_point	rotate(t_trig *t, int x, int y, int z);

// RENDER
void	render_fdf(t_image *image, t_fdf *fdf, t_linedrawer *drawline);

#endif
