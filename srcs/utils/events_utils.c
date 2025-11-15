/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/15 13:51:37 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 14:54:31 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "events.h"

int	is_double_click(int keyboard, int keys)
{
	static long				last_click;
	static struct timeval	curr_click;
	long					delay;

	if (!(keyboard & keys) || gettimeofday(&curr_click, 0) < 0)
		return (0);
	delay = curr_click.tv_usec - last_click;
	last_click = curr_click.tv_usec;
	return (delay <= MAX_DCLICK_DELAY);
}
