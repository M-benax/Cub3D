/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_grid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 08:56:47 by M-benax           #+#    #+#             */
/*   Updated: 2025/10/25 10:16:39 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	compute_size(t_line *start, int *count, int *maxw)
{
	t_line	*it;
	int		l;

	*count = 0;
	*maxw = 0;
	it = start;
	while (it)
	{
		l = (int)ft_strlen(it->text);
		if (l > *maxw)
			*maxw = l;
		*count = *count + 1;
		it = it->next;
	}
}

static int	allocate_and_fill_row(t_map *map, int i, char *text)
{
	int		len;
	int		j;

	len = (int)ft_strlen(text);
	map->grid[i] = (char *)malloc(map->width + 1);
	if (!map->grid[i])
		return (0);
	j = 0;
	while (j < map->width)
	{
		if (j < len)
			map->grid[i][j] = text[j];
		else
			map->grid[i][j] = ' ';
		j++;
	}
	map->grid[i][j] = '\0';
	return (1);
}

static int	fill_grid_rows(t_line *start, t_map *map)
{
	t_line	*it;
	int		i;

	i = 0;
	it = start;
	while (it)
	{
		if (!allocate_and_fill_row(map, i, it->text))
			return (0);
		i++;
		it = it->next;
	}
	return (1);
}

int	build_grid_from_list(t_line *start, t_map *map)
{
	int		count;
	int		maxw;

	if (!start || !map)
		return (0);
	compute_size(start, &count, &maxw);
	if (count == 0)
		return (0);
	map->height = count;
	map->width = maxw;
	map->grid = (char **)malloc(sizeof(char *) * map->height);
	if (!map->grid)
		return (0);
	if (!fill_grid_rows(start, map))
	{
		free_map(map);
		return (0);
	}
	return (1);
}
