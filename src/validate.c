
#include "../includes/cub3d.h"

int	validate_map(t_map *map)
{
	int		i;
	int		j;
	int		player_count;
	char	c;

	if (!map || !map->grid || map->height <= 0 || map->width <= 0)
		return (0);
	player_count = 0;
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			c = map->grid[i][j];
			if (!(c == '0' || c == '1' || c == 'N' || c == 'S' ||
				  c == 'E' || c == 'W' || c == ' '))
				return (0);
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				player_count++;
				map->player_x = i;
				map->player_y = j;
				map->player_dir = c;
			}
			if (c == '0' || c == 'N' || c == 'S' ||
				c == 'E' || c == 'W')
			{
				if (i == 0 || i == map->height - 1 || j == 0 ||
					j == map->width - 1)
					return (0);
				if (map->grid[i - 1][j] == ' ' || map->grid[i + 1][j] == ' ' ||
					map->grid[i][j - 1] == ' ' || map->grid[i][j + 1] == ' ')
					return (0);
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
		return (0);
	return (1);
}