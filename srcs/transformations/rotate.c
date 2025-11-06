/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 11:42:19 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/06 19:34:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point	rotate(t_trig *t, int x, int y, int z)
{
	int					tmp_x;
	int					tmp_y;
	int					tmp_z;

	tmp_x = x;
	tmp_y = y * t->cosine.x + z * -t->sine.x;
	tmp_z = y * t->sine.x +  z * t->cosine.x;
	x = tmp_x * t->cosine.y + tmp_z * t->sine.y;
	y = tmp_y;
	z = tmp_x * -t->sine.y + tmp_z * t->cosine.y;
	return ((t_point){x * t->cosine.z + y * -t->sine.z, x * t->sine.z + y * t->cosine.z});
}
