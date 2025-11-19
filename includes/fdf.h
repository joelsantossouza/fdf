/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 20:48:52 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 23:36:57 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stddef.h>

# define SCREEN_WIDTH	1920
# define SCREEN_HEIGHT	1080

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

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef struct s_img
{
	void	*data;
	char	*addr;
	int		bpp;
	int		linelen;
	int		width;
	int		height;
	t_pos	center;
}	t_img;

typedef struct s_trig
{
	double	sin;
	double	cos;
}	t_trig;

typedef struct s_axis
{
	double	angle_x;
	t_trig	x;
	double	angle_y;
	t_trig	y;
	double	angle_z;
	t_trig	z;
}	t_axis;

typedef int (*t_drawline)(t_img *, t_pos, t_pos, unsigned int);

typedef struct s_fdf
{
	t_pos		*data;
	t_pos		center;
	t_pos		pos;
	t_axis		axis;
	t_drawline	drawline;
	double		zoom;
	double		max_zoom;
	double		min_zoom;
	int			spacing;
	int			scale;
}	t_fdf;

// UTILS
void		putpixel(t_img *img, int x, int y, unsigned int color);
unsigned	brightness(unsigned color, double scale);
int			is_double_click(int keys);

// INITS
int			init_img(void *mlx, t_img *img, int width, int height);
int			init_fdf(t_fdf *fdf, t_pos pos, t_map *map, t_img *img);
int			init_axis(t_axis *axis, double x, double y, double z);

// FREES
void		free_map(t_map *map, void (*free_struct)(void *));
void		free_pic(t_pic *pic, void (*free_struct)(void *));
void		free_img(void *mlx, t_img *img, void (*free_struct)(void *));

// PARSING
int			parse_fdf_file(const char *path, t_map *map);
int			parse_picture(const char *path, unsigned int **pic, int *width, int *height);
int			parse_arguments(char **argv, t_map *map, t_pic *sky, int flags);

// DRAW
int	liangbarsky_clipping(t_pos *p0, t_pos *p1, int width, int height);
int	bresenham_drawline(t_img *img, t_pos p0, t_pos p1, unsigned int color);
int	xiaolinwu_drawline(t_img *img, t_pos p0, t_pos p1, unsigned int color);

// MOTIONS
t_pos	rotate(t_axis *a, int x, int y, int z);
void	control_axis_x(t_axis *a, double change);
void	control_axis_y(t_axis *a, double change);
void	control_axis_z(t_axis *a, double change);

// RENDER
void	render_fdf(t_img *img, t_fdf *fdf, t_map *map);

// EVENTS
int	press_key(int keycode, int *keyboard);
int	release_key(int keycode, int *keyboard);
void	fdf_events(t_fdf *fdf, int keyboard);

#endif
