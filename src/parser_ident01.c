/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ident01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:55:57 by elben-id          #+#    #+#             */
/*   Updated: 2025/10/31 13:54:29 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	set_path(char **dest, char *src)
{
	*dest = ft_strdup(src);
	if (!*dest)
		return (0);
	return (1);
}

static int	parse_identifier_ns(char *line, t_map *map)
{
	char	*p;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->no_set)
			return (0);
		p = line + 3;
		if (!set_path(&map->no_path, p))
			return (0);
		map->no_set = 1;
		return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->so_set)
			return (0);
		p = line + 3;
		if (!set_path(&map->so_path, p))
			return (0);
		map->so_set = 1;
		return (1);
	}
	return (0);
}

static int	parse_identifier_we(char *line, t_map *map)
{
	char	*p;

	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->we_set)
			return (0);
		p = line + 3;
		if (!set_path(&map->we_path, p))
			return (0);
		map->we_set = 1;
		return (1);
	}
	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->ea_set)
			return (0);
		p = line + 3;
		if (!set_path(&map->ea_path, p))
			return (0);
		map->ea_set = 1;
		return (1);
	}
	return (0);
}

int	parse_identifier_line(char *line, t_map *map)
{
	if (parse_identifier_ns(line, map))
		return (1);
	if (parse_identifier_we(line, map))
		return (1);
	return (0);
}
