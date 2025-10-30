typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef t_point	t_vector;

typedef struct s_player
{
	t_point		position;
	t_vector	direction;
	int			zfar;
	double		fov;
}	t_player;

typedef struct s_voxelmap
{
	int	**height;
}	t_voxelmap;

void	render(t_player player, t_map map, image)
{

}

int	main(void)
{
	t_player	player;

	player = (t_player) {
		.position.x =
		.position.y =
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
