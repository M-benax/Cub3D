/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:00:00 by M-benax           #+#    #+#             */
/*   Updated: 2025/10/31 13:47:52 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_line	*consume_identifiers(t_line *head, t_map *map)
{
	t_line	*cur;

	cur = head;
	while (cur)
	{
		if (parse_identifier_line(cur->text, map)
			|| parse_identifier_line2(cur->text, map))
		{
			cur = cur->next;
			continue ;
		}
		break ;
	}
	return (cur);
}

int	parse_cub_file(char *filename, t_map *map)
{
	t_line	*head;
	t_line	*start;

	head = read_file_to_list(filename);
	if (!head)
		return (0);
	start = consume_identifiers(head, map);
	if (!build_grid_from_list(start, map))
	{
		free_list(head);
		return (0);
	}
	free_list(head);
	if (!map->no_set || !map->so_set || !map->we_set || !map->ea_set
		|| !map->f_set || !map->c_set)
		return (0);
	return (validate_map(map));
}
