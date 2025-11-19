/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_axis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 23:34:40 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 23:36:35 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "parsers.h"
#include <math.h>

int	init_axis(t_axis *axis, double x, double y, double z)
{
	axis->angle_x = x;
	axis->angle_y = y;
	axis->angle_z = z;
	axis->x = (t_trig){sin(x), cos(x)};
	axis->y = (t_trig){sin(y), cos(y)};
	axis->z = (t_trig){sin(z), cos(z)};
	return (SUCCESS);
}
