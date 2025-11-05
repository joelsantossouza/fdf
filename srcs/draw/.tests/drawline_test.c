/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawline_test.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/05 16:27:33 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

#define WIDTH	1000
#define HEIGHT	1000
#define SPEED	10

void	*mlx;
void	*window;
t_image	image;

t_point pixel1 = {
	.x = WIDTH / 2,
	.y = HEIGHT / 2,
};

t_point pixel2 = {
	.x = WIDTH + 50,
	.y = HEIGHT / 2,
};

t_linedrawer *drawline = bresenham_drawline;

int	render(int keycode)
{
	ft_bzero(image.addr, WIDTH * HEIGHT * (image.bpp / 8));
	if (keycode == 113)
		drawline = bresenham_drawline;
	else if (keycode == 101)
		drawline = xiaolinwu_drawline;
	else if (keycode == 119)
		pixel1.y-= SPEED;
	else if (keycode == 97)
		pixel1.x-= SPEED;
	else if (keycode == 115)
		pixel1.y+= SPEED;
	else if (keycode == 100)
		pixel1.x+= SPEED;
	else if (keycode == 65362)
		pixel2.y-= SPEED;
	else if (keycode == 65361)
		pixel2.x-= SPEED;
	else if (keycode == 65364)
		pixel2.y+= SPEED;
	else if (keycode == 65363)
		pixel2.x+= SPEED;
	drawline(image, pixel1, pixel2, 0xffffffff);
	mlx_put_image_to_window(mlx, window, image.data, 0, 0);
	return (0);
}

int	main(void)
{
	int	temp;
	mlx = mlx_init();
	if (!mlx)
		return (1);
	window = mlx_new_window(mlx, WIDTH, HEIGHT, "Bresenham test");
	if (!window)
		return (2);
	image.data = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!image.data)
		return (3);
	image.width = WIDTH;
	image.height = HEIGHT;
	image.addr = mlx_get_data_addr(image.data, &image.bpp, &image.linelen, &temp);
	mlx_hook(window, 2, 1L<<0, render, 0);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
