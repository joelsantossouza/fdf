typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef t_point	t_vector;

typedef struct s_camera
{
	t_point		position;
	t_vector	direction;
	int			zfar;
	double		fov;
}	t_camera;

typedef struct s_voxelmap
{
	int	width;
	int	height;
	int	**altitude;
	int	**color;
}	t_voxelmap;

typedef struct s_ray
{
	t_point		position;
	t_vector	direction;
}	t_ray;

typedef struct s_image
{
	int		width;
	int		height;
	char	**data;
}	t_image;

void	render(t_camera camera, t_voxelmap map, t_image image)
{
	t_ray	ray;
	int		zfar;
	int		width;
	int		new_height;
	int		max_height;
	char	color;

	width = -1;
	max_height = 0;
	while (++width < image.width)
	{
		zfar = -1;
		ray = (t_ray) {
			.position = camera.position,
			.direction.x = (-zfar + (zfar - -zfar) / image.width * width) / camera.zfar,
			.direction.y = (zfar + (zfar - zfar) / image.width * width) / camera.zfar,
		};
		while (++zfar < camera.zfar)
		{
			new_height = map.altitude[ray.position.x][ray.position.y];
			if (new_height > max_height)
			{
				color = map.color[ray.position.x][ray.position.y];
				while (max_height < new_height)
					image.data[width][++max_height] = color;
			}
		}
	}
}

int	main(void)
{
	t_player	camera;

	camera = (t_camera) {
		.position.x =
		.position.y =
		.position.z = 
		.direction.x =
		.direction.y =
		.fov =
	};
	while (1)
	{
		render(player, map, image);
		draw_image(image);
	}
}
