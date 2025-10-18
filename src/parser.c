/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:44:34 by M-benax           #+#    #+#             */
/*   Updated: 2025/10/18 12:55:09 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

/*
** Parse a strictly formatted color line: three integers 0..255 separated by
** single commas. Reject empty components (",,") and any non-digit characters
** attached to numbers (e.g. "0m"). Allow whitespace around numbers but not
** inside a numeric token.
*/
static int	parse_color_line(char *line, int *color)
{
	char	*p;
	int		i;
	int		start;
	int		val;

	if (!line || !color)
		return (0);
	p = line;
	i = 0;
	while (i < 3)
	{
		while (*p == ' ' || *p == '\t')
			p++;
		/* require at least one digit for this component */
		if (!is_digit(*p))
			return (0);
		start = 0;
		/* consume digits */
		while (is_digit(p[start]))
			start++;
		/* convert the token (safe because it contains only digits) */
		val = ft_atoi_simple(p);
		if (val < 0 || val > 255)
			return (0);
		color[i++] = val;
		p += start;
		/* after a component: either a comma (for first two) or only spaces/end */
		if (i < 3)
		{
			if (*p != ',')
				return (0);
			p++; /* skip comma and continue to next component */
		}
		else
		{
			/* for last component: allow only spaces/tabs until end */
			while (*p == ' ' || *p == '\t')
				p++;
			if (*p != '\0')
				return (0);
		}
	}
	return (1);
}

static int	parse_identifier_line(char *line, t_map *map)
{
	char	*p;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->no_set)
			return (0);
		p = line + 3;
		map->no_path = ft_strdup(p);
		if (!map->no_path)
			return (0);
		if (open(map->no_path, O_RDONLY) < 0)
			return (0);
		map->no_set = 1;
		return (1);
	}
	if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->so_set)
			return (0);
		p = line + 3;
		map->so_path = ft_strdup(p);
		if (!map->so_path)
			return (0);
		if (open(map->so_path, O_RDONLY) < 0)
			return (0);
		map->so_set = 1;
		return (1);
	}
	if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->we_set)
			return (0);
		p = line + 3;
		map->we_path = ft_strdup(p);
		if (!map->we_path)
			return (0);
		if (open(map->we_path, O_RDONLY) < 0)
			return (0);
		map->we_set = 1;
		return (1);
	}
	return (0);
}

static int	parse_identifier_line2(char *line, t_map *map)
{
	char	*p;

	if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->ea_set)
			return (0);
		p = line + 3;
		map->ea_path = ft_strdup(p);
		if (!map->ea_path)
			return (0);
		if (open(map->ea_path, O_RDONLY) < 0)
			return (0);
		map->ea_set = 1;
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

/*
** Build a linked list of non-empty lines, then process identifiers until map.
*/
int	parse_cub_file(char *filename, t_map *map)
{
	int		fd;
	char	*line;
	t_line	*head;
	t_line	*cur;
	t_line	*tmp;
	int		ret;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		return (0);
	}
	head = NULL;
	cur = NULL;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line && ft_strlen(line) > 0)
		{
			tmp = (t_line *)malloc(sizeof(t_line));
			if (!tmp)
				return (0);
			tmp->text = ft_strdup(line);
			tmp->next = NULL;
			if (!tmp->text)
				return (0);
			if (!head)
				head = tmp;
			else
				cur->next = tmp;
			cur = tmp;
		}
		if (line)
			free(line);
	}
	close(fd);
	/* process list: consume identifier lines (NO,SO,WE,EA,F,C).
	** If any identifier is duplicated the parser returns 0 (invalid).
	*/
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
	/* convert remaining lines to map grid */
	{
		int		count;
		int		i;
		int		maxw;
		t_line	*it;

		it = cur;
		count = 0;
		maxw = 0;
		while (it)
		{
			int l;

			l = (int)ft_strlen(it->text);
			if (l > maxw)
				maxw = l;
			count++;
			it = it->next;
		}
		if (count == 0)
			return (0);
		map->height = count;
		map->width = maxw;
		map->grid = (char **)malloc(sizeof(char *) * map->height);
		if (!map->grid)
			return (0);
		i = 0;
		it = cur;
		while (it)
		{
			int	j;

			map->grid[i] = (char *)malloc(map->width + 1);
			if (!map->grid[i])
				return (0);
			j = 0;
			while (j < map->width)
			{
				if (j < (int)ft_strlen(it->text))
					map->grid[i][j] = it->text[j];
				else
					map->grid[i][j] = ' ';
				j++;
			}
			map->grid[i][j] = '\0';
			i++;
			it = it->next;
		}
		/* free entire list */
		while (head)
		{
			tmp = head->next;
			if (head->text)
				free(head->text);
			free(head);
			head = tmp;
		}
	}
	/* require that all six identifiers were provided exactly once */
	if (!map->no_set || !map->so_set || !map->we_set || !map->ea_set
		|| !map->f_set || !map->c_set)
		return (0);
	return (validate_map(map));
}