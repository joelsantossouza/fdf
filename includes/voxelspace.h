/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/13 12:27:05 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

# define QUADRANT	1.5707963267948966
# define CIRCLE		6.283185307179586476925286766559
# define PI			3.14159265358979323846264338327950288419716939937510
# define GRAVITY	2

typedef struct s_dpoint
{
	double	x;
	double	y;
	double	z;
}	t_dpoint;

typedef struct s_ray
{
	double	x;
	double	y;
	double	dx;
	double	dy;
	int		column;
	int		max_height;
}	t_ray;

typedef struct s_fov
{
	double	plx;
	double	ply;
	double	prx;
	double	pry;
}	t_fov;

typedef struct s_camera
{
	t_dpoint	position;
	t_fov		fov;
	int			horizon;
	int			zfar;
}	t_camera;

typedef struct s_player
{
	t_dpoint	*position;
	t_camera	*cam;
	t_trig		axis_y;
	t_trig		axis_x;
	int			floor;
	double		angle;
	double		height;
	double		speed;
	double		zforce;
	double		climb_max;
	double		sensibility;
}	t_player;

typedef struct s_physic
{
	double	gravity;
	int		unity;
	int		min_horizon;
	int		max_horizon;
}	t_physic;

typedef struct s_vox
{
	void		*mlx;
	void		*window;
	t_image		*img;
	t_player	*player;
	t_map		*map;
	t_pic		*sky;
	t_physic	*world;
	int			keyboard;
}	t_vox;

// UTILS
int				player_mouse(int x, int y, t_vox *vox);

// PARSERS
int		parse_voxel_file(const char *color_file, const char *altitude_file, t_map *map, int heightscale);

// PHYSICS
void	gravity(double *height, double *zforce, int floor, double gravity);

// MOTIONS
void	move_player(t_player *player, double cosine, double sine, t_map *map);
void	rotate_player(t_player *player, double rotation);
int		player_motions(t_vox *vox);

// RENDER
void	render_voxelspace(t_image *img, t_map *map, t_camera *cam, t_pic *sky);

#endif
