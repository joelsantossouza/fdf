/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/09 15:52:24 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	rotate(t_axis *a, int x, int y, int z)
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
	return ((t_point){x * a->z.cos + y * -a->z.sin, x * a->z.sin + y * a->z.cos});
}
