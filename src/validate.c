/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:00:00 by M-benax           #+#    #+#             */
/*   Updated: 2025/10/25 10:54:04 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_allowed(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int	scan_row_for_player(t_map *map, int y)
{
	int		x;
	char	c;

	x = 0;
	while (x < map->width)
	{
		c = map->grid[y][x];
		if (!is_allowed(c))
			return (0);
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			if (map->player_x != -1)
				return (0);
			map->player_x = x;
			map->player_y = y;
			map->player_dir = c;
		}
		x++;
	}
	return (1);
}

static int	locate_player(t_map *map)
{
	int	y;

	map->player_x = -1;
	y = 0;
	while (y < map->height)
	{
		if (!scan_row_for_player(map, y))
			return (0);
		y++;
	}
	if (map->player_x == -1)
		return (0);
	return (1);
}

static int	cell_is_enclosed(t_map *map, int x, int y)
{
	if (x - 1 < 0 || map->grid[y][x - 1] == ' ')
		return (0);
	if (x + 1 >= map->width || map->grid[y][x + 1] == ' ')
		return (0);
	if (y - 1 < 0 || map->grid[y - 1][x] == ' ')
		return (0);
	if (y + 1 >= map->height || map->grid[y + 1][x] == ' ')
		return (0);
	return (1);
}

int	validate_map(t_map *map)
{
	int		y;
	int		x;
	char	c;

	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		return (0);
	if (!locate_player(map))
		return (0);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			c = map->grid[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (!cell_is_enclosed(map, x, y))
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
