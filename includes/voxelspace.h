/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/12 12:34:59 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

# define QUADRANT	1.5707963267948966
# define GRAVITY	2

# define KEY_W			1
# define KEY_S			2
# define KEY_D			4
# define KEY_A			8
# define ARROW_RIGHT	8

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
	double		angle;
	double		height;
	double		speed;
	double		zforce;
	double		climb_max;
	double		sensibility;
}	t_player;

typedef struct s_vox
{
	t_player	*player;
	t_map		*map;
	int			keyboard;
}	t_vox;

// PARSERS
int		parse_voxel_file(const char *color_file, const char *altitude_file, t_map *map, int heightscale);

// PHYSICS
void	gravity(double *height, double *zforce, int floor);

// MOTIONS
void	move_player(t_player *player, t_trig *angle, t_map *map);

// RENDER
void	render_voxelspace(t_image *img, t_map *map, t_camera *cam);

#endif
