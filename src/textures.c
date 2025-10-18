
#include "../includes/cub3d.h"

static int	load_one(t_game *game, char *path, t_img *tex)
{
	tex->img = mlx_xpm_file_to_image(game->mlx, path,
			&tex->width, &tex->height);
	if (!tex->img)
		return (0);
	tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel,
			&tex->line_length, &tex->endian);
	if (!tex->addr)
	{
		mlx_destroy_image(game->mlx, tex->img);
		return (0);
	}
	return (1);
}

int	load_textures(t_game *game)
{
	if (!load_one(game, game->map->no_path, &game->map->textures[0]))
		return (0);
	if (!load_one(game, game->map->so_path, &game->map->textures[1]))
	{
		mlx_destroy_image(game->mlx, game->map->textures[0].img);
		return (0);
	}
	if (!load_one(game, game->map->we_path, &game->map->textures[2]))
	{
		mlx_destroy_image(game->mlx, game->map->textures[0].img);
		mlx_destroy_image(game->mlx, game->map->textures[1].img);
		return (0);
	}
	if (!load_one(game, game->map->ea_path, &game->map->textures[3]))
	{
		mlx_destroy_image(game->mlx, game->map->textures[0].img);
		mlx_destroy_image(game->mlx, game->map->textures[1].img);
		mlx_destroy_image(game->mlx, game->map->textures[2].img);
		return (0);
	}
	return (1);
}

void	free_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->map->textures[i].img)
			mlx_destroy_image(game->mlx, game->map->textures[i].img);
		i++;
	}
}