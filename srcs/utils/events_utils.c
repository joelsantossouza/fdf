/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:51:37 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 15:30:46 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "events.h"

int	is_double_click(int keyboard, int keys)
{
	struct timeval	timeval;
	static long		last_click;
	long			curr_click;
	long			delay;

	if (!(keyboard & keys) || gettimeofday(&timeval, 0) < 0)
		return (0);
	curr_click = timeval.tv_sec * 1000L + timeval.tv_usec / 1000L;
	delay = curr_click - last_click;
	last_click = curr_click;
	return (delay >= MIN_DCLICK_DELAY && delay <= MAX_DCLICK_DELAY);
}
