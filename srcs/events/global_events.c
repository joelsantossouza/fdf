/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 13:36:21 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 23:42:15 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "events.h"
#include "mlx.h"

int	press_key(int keycode, int *keyboard)
{
	if (keycode == 65307)
		*keyboard |= ESC;
	else if (keycode == 119)
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
	else if (keycode == 117)
		*keyboard |= KEY_U;
	else if (keycode == 105)
		*keyboard |= KEY_I;
	else if (keycode == 113)
		*keyboard |= KEY_Q;
	else if (keycode == 101)
		*keyboard |= KEY_E;
	else if (keycode == 111)
		*keyboard |= KEY_O;
	else if (keycode == 65289)
		*keyboard ^= TAB;
	//else if (keycode == 102)
	//	*keyboard ^= KEY_F;
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
	else if (keycode == 117)
		*keyboard &= ~(KEY_U);
	else if (keycode == 105)
		*keyboard &= ~(KEY_I);
	else if (keycode == 113)
		*keyboard &= ~(KEY_Q);
	else if (keycode == 101)
		*keyboard &= ~(KEY_E);
	else if (keycode == 111)
		*keyboard &= ~(KEY_O);
	return (0);
}

void	global_events(void *mlx, t_fdf *fdf, t_vox *vox, int keyboard)
{
	t_cam		*cam;

	if (keyboard & ESC)
		mlx_loop_end(mlx);
	if (keyboard & KEY_E)
		fdf->scale++;
	if (keyboard & KEY_Q)
		fdf->scale--;
	if (keyboard & (KEY_E | KEY_Q))
	{
		cam = &vox->player.cam;
		cam->scale = fdf->scale * 60;
		if (cam->scale < 0)
			cam->scale = 0;
	}
}
