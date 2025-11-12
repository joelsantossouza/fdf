/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joesanto <joesanto@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 22:40:13 by joesanto          #+#    #+#             */
/*   Updated: 2025/11/12 14:11:51 by joesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"
#include "voxelspace.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

#define WIDTH	1500
#define HEIGHT	1000
#define SPEED_JUMP 3 * 1000
#define SPEED	1
#define SENSIBILITY	0.05
#define PI		3.14159265359
#define PLAYER_HEIGHT 20 * 200
#define MAX_HEIGHT_TO_WALK PLAYER_HEIGHT

# define KEY1 65436
# define KEY2 65433
# define KEY3 65435
# define KEY4 65430
# define KEY5 65437
# define KEY6 65432
# define KEY7 65429
# define KEY8 65431

int	render(t_vox *vox)
{
	t_camera *camera = vox->player->cam;
	t_player *player = vox->player;
	t_map	*map = vox->map;
	t_image	*image = vox->img;

	player_motions(vox);
	gravity(&camera->position.z, &player->zforce, map->altitude[map->width * (int)camera->position.y + (int)camera->position.x] + player->height);
	printf("Force: %f\n", player->zforce);
	ft_bzero(image->addr, WIDTH * HEIGHT * (image->bpp / 8));
	render_voxelspace(image, map, camera);
	mlx_put_image_to_window(vox->mlx, vox->window, image->data, 0, 0);
	return (0);
}

int	main(int argc, char **argv)
{
	int	temp;
	t_map	map;
	void	*mlx;
	void	*window;
	t_image	image;
	t_camera	camera;
	t_player	player;

	if (argc == 2)
	{
		if (parse_fdf_file(argv[1], &map) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
	}
	else if (argc == 3)
	{
		if (parse_voxel_file(argv[1], argv[2], &map, 300) < 0)
		{
			ft_fprintf(2, "Fail to load map\n");
			return (1);
		}
	}
	else
	{
		ft_fprintf(2, "Usage: %s <map>\n", *argv);
		return (2);
	}
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
	camera = (t_camera){
		.position.x = map.width / 2.0,
		.position.y = map.height / 5.0,
		.position.z = 300 * 200,
		.horizon = image.height / 2,
		.zfar = 400,
	};
	player = (t_player){
		.position = &camera.position,
		.cam = &camera,
		.height = 100,
		.speed = 3,
		.climb_max = 100,
		.sensibility = 10,
	};
	t_vox vox = {
		mlx,
		window,
		&image,
		&player,
		&map,
		0
	};
	rotate_player(&player, 0);
	mlx_hook(window, 2, 1L<<0, press_key, &vox.keyboard);
	mlx_hook(window, 3, 1L<<1, release_key, &vox.keyboard);
	mlx_loop_hook(mlx, render, &vox);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, image.data);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	return (0);
}
