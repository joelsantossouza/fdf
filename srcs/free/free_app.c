/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_app.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:02:41 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/21 10:31:19 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "voxelspace.h"
#include "mlx.h"
#include <stdlib.h>

void	free_app(t_app *app, void (*free_struct)(void *))
{
	if (app->img.data)
		mlx_destroy_image(app->mlx, app->img.data);
	if (app->window)
		mlx_destroy_window(app->mlx, app->window);
	if (app->mlx)
		mlx_destroy_display(app->mlx);
	free(app->mlx);
	free_map(&app->map, NULL);
	free(app->vox.sky.data);
	free(app->fdf.data);
	*app = (t_app){};
	if (free_struct)
		free_struct(app);
}
