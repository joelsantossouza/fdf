/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_motions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 19:34:08 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_pos	rotate(t_axis *a, int x, int y, int z)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = x;
	tmp_y = y * a->x.cos + z * -a->x.sin;
	tmp_z = y * a->x.sin +  z * a->x.cos;
	x = tmp_x * a->y.cos + tmp_z * a->y.sin;
	y = tmp_y;
	z = tmp_x * -a->y.sin + tmp_z * a->y.cos;
	return ((t_pos){x * a->z.cos + y * -a->z.sin, x * a->z.sin + y * a->z.cos});
}

void	control_axis_x(t_axis *a, double change)
{
	double	new_angle;

	a->angle_x += change;
	new_angle = a->angle_x;
	a->x = (t_trig){sin(new_angle), cos(new_angle)};
}

void	control_axis_y(t_axis *a, double change)
{
	double	new_angle;

	a->angle_y += change;
	new_angle = a->angle_y;
	a->y = (t_trig){sin(new_angle), cos(new_angle)};
}

void	control_axis_z(t_axis *a, double change)
{
	double	new_angle;

	a->angle_z += change;
	new_angle = a->angle_z;
	a->z = (t_trig){sin(new_angle), cos(new_angle)};
}
