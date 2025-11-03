/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   training.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:42:29 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/03 12:14:56 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libs/minilibx-linux/mlx.h"

#define WIDTH	1000
#define HEIGHT	1000

typedef struct t_image
{
	void	*data;
	char	*addr;	
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_image;

void	putpixel(t_image image, int width, int height, unsigned int color)
{
	*(unsigned int *) (image.addr + (image.size_line * height + width * (image.bits_per_pixel / 8))) = color;
}

int	main(void)
{
	void	*mlx = mlx_init();
	if (!mlx)
		return (1);
	void	*window = mlx_new_window(mlx, WIDTH, HEIGHT, "Training");
	if (!window)
		return (2);
	t_image	image;
	image.data = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image.data)
		return (3);
	image.addr = mlx_get_data_addr(image.data, &image.bits_per_pixel, &image.size_line, &image.endian);
	putpixel(image, 10, 10, 0xFFFFFF);
	mlx_put_image_to_window(mlx, window, image.data, 0, 0);
	mlx_loop(mlx);
	return (0);
}
