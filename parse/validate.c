/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:00:00 by M-benax           #+#    #+#             */
/*   Updated: 2025/11/11 15:30:47 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	check_enclosure(t_map *map)
{
	int		y;
	int		x;
	char	c;

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

int	validate_map(t_map *map)
{
	if (!map || !map->grid || map->width <= 0 || map->height <= 0)
		return (0);
	if (!locate_player(map))
		return (0);
	if (!check_enclosure(map))
		return (0);
	fill_spaces_with_walls(map);
	return (1);
}
