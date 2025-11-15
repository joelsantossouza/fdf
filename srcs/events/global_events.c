/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:36:21 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/15 13:24:17 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

int	press_key(int keycode, int *keyboard)
{
	if (keycode == 119)
		*keyboard |= KEY_W;
	else if (keycode == 115)
		*keyboard |= KEY_S;
	else if (keycode == 100)
		*keyboard |= KEY_D;
	else if (keycode == 97)
		*keyboard |= KEY_A;
	else if (keycode == 32)
		*keyboard |= SPACE;
	else if (keycode == 65507)
		*keyboard |= CTRL;
	else if (keycode == 65505)
		*keyboard |= SHIFT;
	return (0);
}

int	release_key(int keycode, int *keyboard)
{
	if (keycode == 119)
		*keyboard &= ~(KEY_W);
	else if (keycode == 115)
		*keyboard &= ~(KEY_S);
	else if (keycode == 100)
		*keyboard &= ~(KEY_D);
	else if (keycode == 97)
		*keyboard &= ~(KEY_A);
	else if (keycode == 32)
		*keyboard &= ~(SPACE);
	else if (keycode == 65507)
		*keyboard &= ~(CTRL);
	else if (keycode == 65505)
		*keyboard &= ~(SHIFT);
	return (0);
}
