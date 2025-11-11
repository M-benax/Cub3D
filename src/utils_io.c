/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:19:26 by elben-id          #+#    #+#             */
/*   Updated: 2025/11/10 15:13:37 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static t_line	*create_node(char *text)
{
	t_line	*node;

	node = (t_line *)malloc(sizeof(t_line));
	if (!node)
	{
		if (text)
			free(text);
		return (NULL);
	}
	node->text = text;
	node->next = NULL;
	return (node);
}

static int	append_node(t_line **head, t_line *node)
{
	t_line	*it;

	if (!head || !node)
		return (0);
	if (!*head)
	{
		*head = node;
		return (1);
	}
	it = *head;
	while (it->next)
		it = it->next;
	it->next = node;
	return (1);
}

static int	process_and_append(t_line **head, char *line)
{
	t_line	*node;

	node = create_node(line);
	if (!node)
		return (0);
	if (!append_node(head, node))
	{
		free(node->text);
		free(node);
		return (0);
	}
	return (1);
}

static int	read_next_and_append(int fd, t_line **head)
{
	char	*line;
	int		r;

	line = NULL;
	r = get_next_line(fd, &line);
	if (r <= 0)
		return (r);
	if (!process_and_append(head, line))
	{
		free_list(*head);
		return (-2);
	}
	return (1);
}

t_line	*read_file_to_list(char *filename)
{
	int		fd;
	t_line	*head;
	int		r;

	if (!filename)
		return (NULL);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	head = NULL;
	while (1)
	{
		r = read_next_and_append(fd, &head);
		if (r == 1)
			continue ;
		break ;
	}
	close(fd);
	if (r == 0)
		return (head);
	return (NULL);
}
