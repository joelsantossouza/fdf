/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/06 16:50:54 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

t_point	rotate(t_rotation *rotation, int x, int y, int z)
{
	const t_rotation	cosine = {cos(rotation->x), cos(rotation->y), cos(rotation->z)};
	const t_rotation	sine = {sin(rotation->x), sin(rotation->y), sin(rotation->z)};
	int					tmp_x;
	int					tmp_y;
	int					tmp_z;

	tmp_x = x;
	tmp_y = y * cosine.x + z * -sine.x;
	tmp_z = y * sine.x +  z * cosine.x;
	x = tmp_x * cosine.y + tmp_z * sine.y;
	y = tmp_y;
	z = tmp_x * -sine.y + tmp_z * cosine.y;
	return ((t_point){x * cosine.z + y * -sine.z, x * sine.z + y * cosine.z});
}
