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

static int	is_empty_line(char *text)
{
	if (!text)
		return (1);
	while (*text)
	{
		if (*text != ' ' && *text != '\t')
			return (0);
		text++;
	}
	return (1);
}

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

static t_line	*skip_empty_lines(t_line *cur)
{
	while (cur && is_empty_line(cur->text))
		cur = cur->next;
	return (cur);
}

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
	t_line	*cur;

	cur = skip_empty_lines(after_map);
	if (cur)
		return (0);
	return (1);
}

static int	build_map_section(t_line *start, t_map *map)
{
	t_line	*map_start;
	t_line	*map_end;
	t_line	*saved_next;

	map_start = skip_empty_lines(start);
	if (!map_start)
		return (0);
	map_end = find_map_end(map_start);
	if (map_end)
	{
		saved_next = map_end->next;
		map_end->next = NULL;
		if (!build_grid_from_list(map_start, map))
		{
			map_end->next = saved_next;
			return (0);
		}
		map_end->next = saved_next;
		if (!validate_no_content_after_map(map_end))
			return (0);
	}
	else
	{
		if (!build_grid_from_list(map_start, map))
			return (0);
	}
	return (1);
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
