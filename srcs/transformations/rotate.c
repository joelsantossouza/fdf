/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 11:19:11 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	rotate(t_axis *a, int x, int y, int z)
{
	int	tmp_x;
	int	tmp_y;
	int	tmp_z;

	tmp_x = x;
	tmp_y = y * a->x.cosine + z * -a->x.sine;
	tmp_z = y * a->x.sine +  z * a->x.cosine;
	x = tmp_x * a->y.cosine + tmp_z * a->y.sine;
	y = tmp_y;
	z = tmp_x * -a->y.sine + tmp_z * a->y.cosine;
	return ((t_point){x * a->z.cosine + y * -a->z.sine, x * a->z.sine+ y * a->z.cosine});
}
