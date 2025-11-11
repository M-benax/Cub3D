/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:32:00 by elben-id          #+#    #+#             */
/*   Updated: 2025/11/11 15:32:01 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_allowed(char c)
{
	if (c == '0' || c == '1' || c == ' ')
		return (1);
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	scan_row_for_player(t_map *map, int y)
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

int	locate_player(t_map *map)
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

int	cell_is_enclosed(t_map *map, int x, int y)
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

void	fill_spaces_with_walls(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == ' ')
				map->grid[y][x] = '1';
			x++;
		}
		y++;
	}
}
