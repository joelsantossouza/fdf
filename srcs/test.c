#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <math.h>
#include "minilibx-linux/mlx.h"


typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_camera
{
	t_point		position;
	t_vector	direction;
	int			height;
	int			zfar;
	double		fov;
}	t_camera;

typedef struct s_voxelmap
{
	unsigned int	width;
	unsigned int	height;
	int				*altitude;
	unsigned int	*color;
}	t_voxelmap;

typedef struct s_ray
{
	t_point		position;
	t_vector	direction;
}	t_ray;

typedef struct s_image
{
	unsigned int	width;
	unsigned int	height;
	void			*mlx;
	void			*window;
}	t_image;

void	render(t_camera camera, t_voxelmap map, t_image image)
{
	t_ray			ray;
	int				zfar;
	unsigned int	width;
	int				new_height;
	int				max_height;
	unsigned int	color;
	int				offset;
	const int		end = map.width * map.height;

	// camera.zfar = 0 DOES SEGFAULT
	width = -1;
	while (++width < image.width)
	{
		zfar = 0;
		max_height = 0;
		ray = (t_ray) {
			.position = camera.position,
			.direction.x = (-camera.zfar + (camera.zfar - -camera.zfar) / (double) image.width * width) / camera.zfar,
			.direction.y = (camera.zfar + (camera.zfar - camera.zfar) / (double) image.width * width) / camera.zfar,
		};
		while (++zfar < camera.zfar)
		{
			offset = ray.position.x * ray.position.y;
			if (offset >= end)
				break ;
			new_height = (map.altitude[offset] / zfar * 50) - camera.height;
			if (new_height > max_height)
			{
				color = map.color[offset];
				while (max_height < new_height)
					mlx_pixel_put(image.mlx, image.window, width, ++max_height, color);
			}
			ray.position.x = round(ray.position.x + ray.direction.x);
			ray.position.y = round(ray.position.y + ray.direction.y);
		}
	}
}

int	validate_file_map(t_voxelmap *map, const char *path)
{
	const int	file = open(path, O_RDONLY);
	char		*line;
	int			total_size;

	*map = (t_voxelmap) {};
	if (file < 0)
		return (-1);
	line = 0;
	if (get_next_line(&line, file) < 0)
		return (close(file), -1);
	map->width = ft_word_count(line, ' ');
	map->height = 1;
	while (line)
	{
		if (ft_word_count(line, ' ') != map->width)
			return (close(file), free(line), -1);
		if (get_next_line(&line, file) < 0)
			return (close(file), -1);
		map->height++;
	}
	if (close(file) < 0)
		return (-1);
	total_size = map->width * map->height;
	map->altitude = malloc(sizeof(int) * total_size);
	if (!map->altitude)
		return (-1);
	map->color = malloc(sizeof(int) * total_size);
	if (!map->color)
		return (free(map->altitude), -1);
	return (0);
}

int	import_map(t_voxelmap *map, const char *path)
{
	const int	file = open(path, O_RDONLY);
	char		*line;
	char		*ptr;
	int			i;

	if (file < 0)
		return (-1);
	if (validate_file_map(map, path) < 0)
		return (close(file), -1);
	line = 0;
	if (get_next_line(&line, file) < 0)
		return (close(file), -1);
	i = -1;
	while (line)
	{
		ptr = line;
		while (*ptr && *ptr != '\n')
		{
			map->altitude[++i] = ft_atol_base(ptr, &ptr, "0123456789");
			while (*ptr++ != 'x')
				;
			map->color[i] = ft_atol_base(ptr, &ptr, "0123456789abcdef");
		}
		if (get_next_line(&line, file) < 0)
			return (close(file), -1);
	}
	if (close(file) < 0)
		return (-1);
	return (0);
}

int	main(void)
{
	t_voxelmap	map;
	t_image		image;
	t_camera	camera;

	image = (t_image) {
		.width = 1000,
		.height = 600,
	};
	image.mlx = mlx_init();
	if (!image.mlx)
		return (1);
	image.window = mlx_new_window(image.mlx, image.width, image.height, "Voxel");
	if (!image.window)
		return (1);
	if (import_map(&map, "map") < 0)
		return (1);
	camera = (t_camera) {
		.position.x = map.width + map.width / 2,
		.position.y = map.height / 4,
		.height = 1,
		.direction.x = 0,
		.direction.y = 0,
		.zfar = 30,
	};
	render(camera, map, image);
	mlx_loop(image.mlx);
	return (0);
}
