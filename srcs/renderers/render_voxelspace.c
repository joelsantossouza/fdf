/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 11:36:58 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/07 22:13:04 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

#define PI	3.14159265359

void render_voxelspace(t_image *image, t_voxelspace *vox, t_camera *camera)
{
	double	fov = PI / 180 * 60;
    for (int x = 0; x < image->width; ++x)
    {
        double ray_angle = 6.34 - fov / 2.0
                         + (x / (double)image->width) * fov;

        double dx = cos(ray_angle) * 0.9;
        double dy = sin(ray_angle) * 0.9;

        double px = camera->position.x;
        double py = camera->position.y;

        int max_height = image->height;

        for (int z = 1; z < camera->zfar; ++z)
        {
            px += dx;
            py += dy;

            int map_x = (int)px;
            int map_y = (int)py;
            if (map_x < 0 || map_x >= vox->map->width || map_y < 0 || map_y >= vox->map->height)
                break;

            int height = vox->map->altitude[vox->map->width * map_y + map_x];
            int screen_y = (camera->altitude - height) * vox->scale / z + image->height / 2;
			if (screen_y < 0)
				screen_y = 0;

            if (screen_y < max_height)
            {
                unsigned int color = vox->map->color[vox->map->width * map_y + map_x];
				while (max_height > screen_y)
					putpixel(image, x, --max_height, color);
            }
        }
    }
}

