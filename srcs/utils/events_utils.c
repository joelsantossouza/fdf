/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:51:37 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 17:33:21 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "events.h"

int	is_double_click(int keys)
{
	static int		last_keys = -1;
	struct timeval	timeval;
	static long		last_click;
	long			curr_click;
	int				result;

	if (gettimeofday(&timeval, 0) < 0)
		return (0);
	curr_click = timeval.tv_sec * 1000L + timeval.tv_usec / 1000L;
	result = keys == last_keys && curr_click - last_click < MAX_DCLICK_DELAY;
	last_keys = keys;
	last_click = curr_click;
	return (result);
}
