/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 21:32:45 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

# define QUADRANT	1.5707963267948966
# define CIRCLE		6.283185307179586476925286766559
# define PI			3.14159265358979323846264338327950288419716939937510

typedef struct s_dpos2
{
	double	x;
	double	y;
}	t_dpos2;

typedef struct s_dpos3
{
	double	x;
	double	y;
	double	z;
}	t_dpos3;

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

typedef struct s_cam
{
	t_dpos3	pos;
	t_fov	fov;
	int		horizon;
	int		zfar;
	int		scale;
}	t_cam;

typedef void (*t_moveplayer)();

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
	t_dpos3			*pos;
	t_cam			*cam;
	t_trig			axis_y;
	t_trig			axis_x;
	double			angle;
	t_moveplayer	move;
	int				floor;
	double			speed;
	double			zforce;
	t_player_stats	*stats;
}	t_player;

typedef struct s_vox
{
	t_player	player;
	t_pic		sky;
	double		gravity;
	int			min_horizon;
	int			max_horizon;
}	t_vox;

typedef struct s_app
{
	void	*mlx;
	void	*window;
	t_img	img;
	t_map	map;
	t_fdf	fdf;
	t_vox	vox;
	double	fps;
	int		keyboard;
}	t_app;

// PARSERS
int		parse_voxel_file(const char *color_file, const char *height_file, t_map *map);

// PHYSICS
void	gravity(double *height, double *zforce, int floor, double gravity);
void	player_physics(t_player *player, double gravity_force);

// MOTIONS
void	player_walk(t_player *player, double sine, double cosine, t_map *map);
void	player_fly(t_player *player, double sine, double cosine, t_map *map);
void	rotate_player(t_player *player, double rotation);

// RENDER
void	render_voxelspace(t_img *img, t_map *map, t_cam *cam, t_pic *sky);

// EVENTS
void	global_events(t_app *app);
int		player_mouse(int x, int y, t_app *app);
void	player_events(t_player *player, t_map *map, double fps, int keyboard);

// LOOPS
int	app_loop(t_app *app);

#endif
