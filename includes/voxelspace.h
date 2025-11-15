/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 17:13:15 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

# define QUADRANT	1.5707963267948966
# define CIRCLE		6.283185307179586476925286766559
# define PI			3.14159265358979323846264338327950288419716939937510

typedef struct s_dpoint2
{
	double	x;
	double	y;
}	t_dpoint2;

typedef struct s_dpoint3
{
	double	x;
	double	y;
	double	z;
}	t_dpoint3;

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
	t_dpoint3	pos;
	t_fov		fov;
	int			horizon;
	int			zfar;
}	t_camera;

typedef void (t_move_func)();

typedef struct s_player_stats
{
	double	height;
	double	speed_max;
	double	run_speed_max;
	double	climb_max;
	double	jump_force;
	double	dive_force;
	double	sensibility;
}	t_player_stats;

typedef struct s_player
{
	t_dpoint3		*pos;
	t_camera		*cam;
	t_trig			axis_y;
	t_trig			axis_x;
	double			angle;
	t_move_func		*move;
	int				floor;
	double			speed;
	double			zforce;
	t_player_stats	*stats;
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

// PARSERS
int		parse_voxel_file(const char *color_file, const char *altitude_file, t_map *map, int heightscale);

// PHYSICS
void	gravity(double *height, double *zforce, int floor, double gravity);

// MOTIONS
void	player_walk(t_player *player, double sine, double cosine, t_map *map);
void	player_fly(t_player *player, double sine, double cosine, t_map *map);
void	rotate_player(t_player *player, double rotation);

// RENDER
void	render_voxelspace(t_image *img, t_map *map, t_camera *cam, t_pic *sky);

// EVENTS
int		player_mouse(int x, int y, t_vox *vox);
int		player_events(t_vox *vox);

// LOOPS
int	voxelspace_loop(t_vox *vox);

#endif
