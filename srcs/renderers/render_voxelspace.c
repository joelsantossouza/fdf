/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:36:58 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/07 11:55:18 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_voxelspace(t_image *image, t_voxelspace *vox, t_camera *camera)
{
	int		i;
	int		z;
	t_angle	delta;
	t_point	p;

	i = -1;
	while (++i < image->width)
	{
		delta.x = ((camera->zfar * 2) / image->width * i) / camera.zfar;
		delta.y = ((0) / image->width * i) / camera.zfar;
		z = 0;
		while (++z < camera.zfar)
		{
		}
	}
}
