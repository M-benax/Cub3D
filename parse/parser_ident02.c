/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ident02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 13:51:52 by elben-id          #+#    #+#             */
/*   Updated: 2025/10/31 13:54:15 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	is_empty_line(char *text)
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

t_line	*consume_identifiers(t_line *head, t_map *map)
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

t_line	*skip_empty_lines(t_line *cur)
{
	while (cur && is_empty_line(cur->text))
		cur = cur->next;
	return (cur);
}

static int	parce_space_in_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != ' ' && line[i] != '\0')
		return (0);
	return (1);
}

int	parse_identifier_line2(char *line, t_map *map)
{
	if (!line || parce_space_in_line(line))
	{
		return (1);
	}
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->f_set)
			return (0);
		if (!parse_color_line(line + 2, map->floor_color))
			return (0);
		map->f_set = 1;
		return (1);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->c_set)
			return (0);
		if (!parse_color_line(line + 2, map->ceiling_color))
			return (0);
		map->c_set = 1;
		return (1);
	}
	return (0);
}
