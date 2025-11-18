/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 23:16:35 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 00:02:58 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

double	get_fps(void)
{
	struct timeval	timeval;
	static double	last_frame;
	double			curr_frame;
	double			delta_time;

	if (gettimeofday(&timeval, 0) < 0)
		return (0);
	curr_frame = timeval.tv_sec + timeval.tv_usec * 0.000001;
	delta_time = curr_frame - last_frame;
	last_frame = curr_frame;
	return (delta_time);
}
