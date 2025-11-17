/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_main.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:00:00 by M-benax           #+#    #+#             */
/*   Updated: 2025/11/10 15:13:27 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_line	*find_map_end(t_line *start)
{
	t_line	*cur;

	cur = start;
	while (cur && !is_empty_line(cur->text))
		cur = cur->next;
	return (cur);
}

static int	validate_no_content_after_map(t_line *after_map)
{
	return (!skip_empty_lines(after_map));
}

static int	build_map_with_end(t_line *map_start, t_line *map_end, t_map *map)
{
	t_line	*saved_next;

	saved_next = map_end->next;
	map_end->next = NULL;
	if (!build_grid_from_list(map_start, map))
	{
		map_end->next = saved_next;
		return (0);
	}
	map_end->next = saved_next;
	return (validate_no_content_after_map(map_end));
}

static int	build_map_section(t_line *start, t_map *map)
{
	t_line	*map_start;
	t_line	*map_end;

	map_start = skip_empty_lines(start);
	if (!map_start)
		return (0);
	map_end = find_map_end(map_start);
	if (map_end)
		return (build_map_with_end(map_start, map_end, map));
	return (build_grid_from_list(map_start, map));
}

int	parse_cub_file(char *filename, t_map *map)
{
	t_line	*head;
	t_line	*start;

	head = read_file_to_list(filename);
	if (!head)
		return (0);
	start = consume_identifiers(head, map);
	if (!build_map_section(start, map))
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
