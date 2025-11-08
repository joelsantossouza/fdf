/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_voxelspace.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:03:28 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/08 16:59:12 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"
#include "libft.h"

static inline
void	draw_column(t_image *image, t_point p, int zfar, t_vox *vox)
{
	unsigned 	color;
	const long	offset = vox->map->width * p.y + p.x;
	const int	height = ft_max(
		0,
		image->height - (vox->map->altitude[offset] - vox->camera->altitude) / zfar * vox->scale
	);

	if (height < vox->max_height)
	{
		color = vox->map->color[offset];
		while (vox->max_height-- > height)
			putpixel(image, vox->column, vox->max_height, color);
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
	if (liangbarsky_clipping(&p0, &p1, image->width - 1, image->height - 1) < 0)
		return (-1);
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

void	render_voxelspace(t_image *image, t_vox *vox)
{
	vox->column = -1;
	while (++vox->column < image->width)
	{
	}
}
