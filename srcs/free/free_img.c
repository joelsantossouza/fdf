/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:13:17 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/21 10:32:20 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "mlx.h"

void	free_img(void *mlx, t_img *img, void (*free_struct)(void *))
{
	if (img->data)
		mlx_destroy_image(mlx, img->data);
	*img = (t_img){};
	if (free_struct)
		free_struct(img);
}
