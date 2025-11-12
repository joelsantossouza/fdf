/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gravity.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 19:19:20 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/12 16:17:09 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	gravity(double *height, double *zforce, int floor, double gravity)
{
	const double	next_height = *height + *zforce;
	static int		acceleration;

	if (next_height <= floor)
	{
		*height = floor;
		*zforce = 0;
		acceleration = 0;
	}
	else
	{
		acceleration++;
		*height = next_height;
		*zforce -= gravity * acceleration;
	}
}
