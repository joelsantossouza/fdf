#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int	main(void)
{
	void	*mlx;
	void	*window;
	void	*image;

	(void)image;
	mlx = mlx_init();
	if (!mlx)
		return (1);
	window = mlx_new_window(mlx, 1920, 1080, "test");
	if (!window)
	{
		mlx_destroy_display(mlx);
		free(mlx);
		return (1);
	}
	mlx_loop(mlx);
	mlx_destroy_window(mlx, window);
	mlx_destroy_display(mlx);
	free(mlx);
	return (0);
}
