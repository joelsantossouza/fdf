/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 00:22:47 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include "libft.h"

static inline
void	draw_column(t_image *image, t_point	p, int zfar, t_vox *vox)
{
	const t_map	*map = vox->map;
	const long	offset = map->width * p.y + p.x;
	unsigned 	color;
	int			height;

	height = (vox->camera->altitude - map->altitude[offset]) * vox->scale / zfar + image->height / 2;
	if (height < 0)
		height = 0;
	if (height < vox->max_height)
	{
		color = map->color[offset];
		while (vox->max_height > height)
			putpixel(image, vox->column, --vox->max_height, color);
	}
}

static inline
void	raymarch_horizontal(t_image *image, t_point p0, t_point p1, t_vox *vox)
{
	const t_point	delta = {p1.x - p0.x, p1.y - p0.y};
	const int		dir = 1 - 2 * (delta.y < 0);
	const t_point	inc = {delta.x<<1, (delta.y * dir)<<1};
	const int		start_x = p0.x;
	int				decision;

	decision = inc.y - delta.x;
	while (p0.x++ <= p1.x)
	{
		if (decision >= 0)
		{
			p0.y += dir;
			decision -= inc.x;
		}
		draw_column(image, p0, p0.x - start_x, vox);
		decision += inc.y;
	}
}

static inline
void	raymarch_vertical(t_image *image, t_point p0, t_point p1, t_vox *vox)
{
	const t_point	delta = {p1.x - p0.x, p1.y - p0.y};
	const int		dir = 1 - 2 * (delta.x < 0);
	const t_point	inc = {(delta.x * dir)<<1, delta.y<<1};
	const int		start_y = p0.y;
	int				decision;

	decision = inc.x - delta.y;
	while (p0.y++ <= p1.y)
	{
		if (decision >= 0)
		{
			p0.x += dir;
			decision -= inc.y;
		}
		draw_column(image, p0, p0.y - start_y, vox);
		decision += inc.x;
	}
}

static inline
int	raymarch(t_image *image, t_point p0, t_point p1, t_vox *vox)
{
	// RETURN GOOD VALUE
	if (ft_abs(p1.x - p0.x) > ft_abs(p1.y - p0.y))
	{
		if (p0.x <= p1.x)
			raymarch_horizontal(image, p0, p1, vox);
		else
			raymarch_horizontal(image, p1, p0, vox);
	}
	else
	{
		if (p0.y <= p1.y)
			raymarch_vertical(image, p0, p1, vox);
		else
			raymarch_vertical(image, p1, p0, vox);
	}
	return (0);
}

#include <math.h>
void render_voxelspace(t_image *image, t_vox *vox)
{
    const t_camera *camera = vox->camera;

    // Direction and right vectors (must be normalized)
    t_vector dir = camera->direction;
    t_vector right = { dir.y, -dir.x };

    // Far plane center and width
    double half_width = camera->zfar * atan(camera->fov / 2.0);
    t_point far_center = {
        camera->position.x + dir.x * camera->zfar,
        camera->position.y + dir.y * camera->zfar
    };

    // Far plane corners
    t_point far_left = {
        far_center.x - right.x * half_width,
        far_center.y - right.y * half_width
    };
    t_point far_right = {
        far_center.x + right.x * half_width,
        far_center.y + right.y * half_width
    };

    // Increment per screen column
    t_vector inc = {
        (far_right.x - far_left.x) / (double) (image->width - 1),
        (far_right.y - far_left.y) / (double) (image->width - 1)
    };

    // Render each column
    t_point current = far_left;
    for (vox->column = 0; vox->column < image->width; ++vox->column)
    {
        vox->max_height = image->height;
        raymarch(image, camera->position, current, vox);

        current.x = far_left.x + inc.x * vox->column;
        current.y = far_left.y + inc.y * vox->column;
    }
}
