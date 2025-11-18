/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:48:50 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/18 19:44:55 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include "mlx.h"
#include "parsers.h"

int	init_img(void *mlx, t_img *img, int width, int height)
{
	int	tmp;

	img->data = mlx_new_image(mlx, width, height);
	if (!img->data)
		return (*img = (t_img){}, ERROR);
	img->addr = mlx_get_data_addr(img->data, &img->bpp, &img->linelen, &tmp);
	if (!img->addr)
		return (free_img(img, NULL), ERROR);
	img->bpp >>= 3;
	img->width = width;
	img->height = height;
	img->center = (t_pos){width >> 1, height >> 1};
	return (SUCCESS);
}
