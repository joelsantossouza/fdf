/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:36:21 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/12 15:06:09 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	else if (keycode == 65363)
		*keyboard |= ARROW_RIGHT;
	else if (keycode == 65361)
		*keyboard |= ARROW_LEFT;
	else if (keycode == 32)
		*keyboard |= SPACE;
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
	else if (keycode == 65363)
		*keyboard &= ~(ARROW_RIGHT);
	else if (keycode == 65361)
		*keyboard &= ~(ARROW_LEFT);
	else if (keycode == 32)
		*keyboard &= ~(SPACE);
	return (0);
}
