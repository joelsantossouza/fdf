/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 16:46:06 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

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

typedef struct s_camera
{
	t_point		position;
	t_trig		angle;
	int			horizon;
	int			altitude;
	int			zfar;
	int			scale;
}	t_camera;

// RENDER
void	render_voxelspace(t_image *img, t_map *map, t_camera *cam);

#endif
