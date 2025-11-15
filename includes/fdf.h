/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 17:36:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>

# define WHITE	0xFFFFFFFF
# define BLACK	0x00000000

typedef struct s_pic
{
	int				width;
	int				height;
	unsigned int	*data;
}	t_pic;

typedef struct s_map
{
	int			width;
	int			height;
	long		total;
	unsigned	*color;	
	int			*altitude;	
}	t_map;

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_image
{
	void	*data;
	char	*addr;
	int		bpp;
	int		linelen;
	int		width;
	int		height;
	t_point	center;
}	t_image;

typedef struct s_trig
{
	double	sin;
	double	cos;
}	t_trig;

typedef struct s_axis
{
	t_trig	x;
	t_trig	y;
	t_trig	z;
}	t_axis;

typedef struct s_fdf
{
	t_map	*map;
	t_point	center;
	t_point	pos;
	t_point	*transformed;
	t_axis	axis;
	double	zoom;
	int		spacing;
}	t_fdf;

typedef int (t_linedrawer)(t_image *, t_point, t_point, unsigned int);

// UTILS
void		free_map(t_map *map, void (*free_struct)(void *));
void		putpixel(t_image *img, int x, int y, unsigned color);
unsigned	brightness(unsigned color, double scale);
int			is_double_click(int keys);

// PARSING
int			parse_fdf_file(const char *path, t_map *map);
int			parse_picture(const char *path, unsigned int **pic, int *width, int *height);

// DRAW
int	liangbarsky_clipping(t_point *p0, t_point *p1, int width, int height);
int	bresenham_drawline(t_image *img, t_point p0, t_point p1, unsigned color);
int	xiaolinwu_drawline(t_image *img, t_point p0, t_point p1, unsigned color);

// TRANSFORMATION
t_point	rotate(t_axis *a, int x, int y, int z);

// RENDER
void	render_fdf(t_image *img, t_fdf *fdf, t_linedrawer *drawline);

// EVENTS
int	press_key(int keycode, int *keyboard);
int	release_key(int keycode, int *keyboard);

#endif
