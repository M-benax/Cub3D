/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 08:56:47 by M-benax           #+#    #+#             */
/*   Updated: 2025/11/11 19:29:38 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	free_list(t_line *head)
{
	t_line	*tmp;
	t_line	*it;

	it = head;
	while (it)
	{
		tmp = it->next;
		if (it->text)
			free(it->text);
		free(it);
		it = tmp;
	}
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	if (map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
	if (map->no_path)
		free(map->no_path);
	if (map->so_path)
		free(map->so_path);
	if (map->we_path)
		free(map->we_path);
	if (map->ea_path)
		free(map->ea_path);
}

void	print_error(char *message)
{
	write(2, "Error:\n", 7);
	write(2, message, ft_strlen(message));
}
