/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/16 11:11:48 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/16 20:36:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "events.h"

static inline
void	handle_space_event(int keyboard, t_drawline *drawline)
{
	static int	was_released = 1;

	if (!(keyboard & SPACE))
		was_released = 1;
	else if (was_released)
	{
		if (*drawline == bresenham_drawline)
			*drawline = xiaolinwu_drawline;
		else
			*drawline = bresenham_drawline;
		was_released = 0;
	}
}

void	fdf_events(t_fdf_stats *fdf_stats, int keyboard)
{
	handle_space_event(keyboard, &fdf_stats->drawline);
	if (keyboard & KEY_W)
		fdf_stats->pos.y--;
	if (keyboard & KEY_S)
		fdf_stats->pos.y++;
	if (keyboard & KEY_D)
		fdf_stats->pos.x++;
	if (keyboard & KEY_A)
		fdf_stats->pos.x--;
	if (keyboard & SHIFT)
		fdf_stats->zoom *= 1.1;
	if (keyboard & CTRL)
		fdf_stats->zoom /= 1.1;
	if (keyboard & KEY_J)
		control_axis_x(&fdf_stats->axis, -0.1);
	if (keyboard & KEY_K)
		control_axis_x(&fdf_stats->axis, +0.1);
	if (keyboard & KEY_H)
		control_axis_y(&fdf_stats->axis, +0.1);
	if (keyboard & KEY_L)
		control_axis_y(&fdf_stats->axis, -0.1);
	if (keyboard & KEY_U)
		control_axis_z(&fdf_stats->axis, -0.1);
	if (keyboard & KEY_I)
		control_axis_z(&fdf_stats->axis, +0.1);
}
