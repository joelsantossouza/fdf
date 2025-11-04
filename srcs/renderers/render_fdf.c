/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fdf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 15:11:03 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/04 23:19:36 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	render_fdf(t_image image, t_fdf fdf, t_linedrawer *drawline)
{
	t_point	back;
	t_point	start = (t_point) {.x = fdf.position.x, .y = fdf.position.y};
	unsigned int	i;
	unsigned int	j;

	back.y = 0;
	j = 0;
	while (j < fdf.map.height)
	{
		back.x = 0;
		i = 0;
		while (i < fdf.map.width)
		{
			drawline(image, (t_point) {
				.x = start.x + back.x * fdf.spacing,
				.y = start.y + back.y * fdf.spacing,
			},
			(t_point) {
				.x = start.x + i * fdf.spacing,
				.y = start.y + j * fdf.spacing,
			}, 0xffffffff);
			back.x = i++;
		}
		back.y = j++;
	}
}
