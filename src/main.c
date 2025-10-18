
#include "../includes/cub3d.h"

static void	print_error_and_cleanup(char *msg, t_map *map)
{
	printf("Error\n%s\n", msg);
	free_map(map);
	exit(1);
}

static void	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_map	map;

	check_args(argc, argv);
	ft_bzero(&map, sizeof(map));
	game.map = &map;
	if (!parse_cub_file(argv[1], &map))
		print_error_and_cleanup("Invalid map file", &map);
	if (!init_game(&game))
		print_error_and_cleanup("Failed to initialize game", &map);
	if (!load_textures(&game))
		print_error_and_cleanup("Failed to load textures", &map);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 17, 1L << 17, close_window, &game);
	mlx_loop(game.mlx);
	free_textures(&game);
	free_map(&map);
	return (0);
}