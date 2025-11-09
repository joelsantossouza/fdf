/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   voxelspace.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 14:58:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 00:17:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VOXELSPACE_H
# define VOXELSPACE_H

# include "fdf.h"

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_camera
{
	t_point		position;
	t_vector	direction;
	int			altitude;
	int			zfar;
	double		fov;
	double		fov_half;
}	t_camera;

typedef struct s_vox
{
	t_map		*map;
	int			scale;
	t_camera	*camera;
	int			max_height;
	int			column;
}	t_vox;

// RENDER
void	render_voxelspace(t_image *image, t_vox *vox);

#endif
