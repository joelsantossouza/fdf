/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/11 11:13:42 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

# define GRAVITY	2

typedef struct s_dpoint
{
	double	x;
	double	y;
}	t_dpoint;

typedef t_dpoint	t_vector;

typedef struct s_ray
{
	t_dpoint	position;
	t_vector	direction;
	int			column;
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
	double		altitude;
	int			horizon;
	int			zfar;
}	t_camera;

// PARSERS
int		parse_voxel_file(const char *color_file, const char *altitude_file, t_map *map, int heightscale);

// PHYSICS
void	gravity(double *height, double *zforce, int floor);

// RENDER
void	render_voxelspace(t_image *img, t_map *map, t_camera *cam);

#endif
