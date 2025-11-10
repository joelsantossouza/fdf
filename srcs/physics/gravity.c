/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:19:20 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/10 20:38:49 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"

void	gravity(double *height, double *zforce, int floor)
{
	const double	next_height = *height + *zforce;

	if (next_height <= floor)
	{
		*height = floor;
		*zforce = 0;
	}
	else
	{
		*height = next_height;
		*zforce -= GRAVITY;
	}
}
