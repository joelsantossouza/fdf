/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 11:36:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/19 11:51:05 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "voxelspace.h"

int	main(int argc, char **argv)
{
	t_app	app;

	if (init_app(&app) < 0)
		return (1);
	mlx_mouse_hide(app.mlx, app.window);
	mlx_hook(app.window, 2, 1L << 0, press_key, &app.keyboard);
	mlx_hook(app.window, 3, 1L << 1, release_key, &app.keyboard);
	mlx_hook(app.window, 6, 1L << 6, player_mouse, &app);
	mlx_loop_hook(app.mlx, app_loop, &app);
	mlx_loop(app.mlx);
	return (free_app(&app, NULL), 0);
}
