#include "../parsers.h"
#include "fdf.h"
#include "libft.h"

int	main(int argc, char **argv)
{
	t_map	map;
	t_pic	sky;
	int		result;

	(void)argc;
	if ((result = parse_arguments(argv, &map, &sky, 0)) < 0)
	{
		ft_fprintf(1, "Fail parsing arguments\n");
		return (1);
	}
	if (result & MAP_DONE)
	{
		ft_printf("\n--- T_MAP ---\n");
		ft_printf("width: %d\n", map.width);
		ft_printf("height: %d\n", map.height);
		ft_printf("\n");
		free_map(&map, NULL);
	}
	if (result & SKY_DONE)
	{
		ft_printf("\n--- T_SKY ---\n");
		ft_printf("width: %d\n", sky.width);
		ft_printf("height: %d\n", sky.height);
		ft_printf("\n");
		free_pic(&sky, NULL);
	}
	return (0);
}
