/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:36:21 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/16 11:46:09 by joesanto         ###   ########.fr       */
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
	else if (keycode == 104)
		*keyboard |= KEY_H;
	else if (keycode == 108)
		*keyboard |= KEY_L;
	else if (keycode == 106)
		*keyboard |= KEY_J;
	else if (keycode == 107)
		*keyboard |= KEY_K;
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
	else if (keycode == 104)
		*keyboard &= ~(KEY_H);
	else if (keycode == 108)
		*keyboard &= ~(KEY_L);
	else if (keycode == 106)
		*keyboard &= ~(KEY_J);
	else if (keycode == 107)
		*keyboard &= ~(KEY_K);
	return (0);
}
