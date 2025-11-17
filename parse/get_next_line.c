/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:31:04 by elben-id          #+#    #+#             */
/*   Updated: 2025/10/24 16:31:08 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static ssize_t	gnl_read_to_res(int fd, char **res)
{
	char	c;
	ssize_t	r;

	*res = NULL;
	r = read(fd, &c, 1);
	while (r > 0)
	{
		if (c == '\n')
			break ;
		*res = append_char(*res, c);
		if (!*res)
			return (-1);
		r = read(fd, &c, 1);
	}
	return (r);
}

static int	gnl_handle_error_and_eof(char **line, char *res, ssize_t r)
{
	if (r < 0)
	{
		if (res)
			free(res);
		return (-1);
	}
	if (r == 0 && !res)
	{
		*line = NULL;
		return (0);
	}
	return (2);
}

static int	gnl_assign_line(char **line, char *res)
{
	char	*tmp;

	if (res)
	{
		*line = res;
		return (1);
	}
	tmp = ft_strdup("");
	if (!tmp)
		return (-1);
	*line = tmp;
	return (1);
}

int	get_next_line(int fd, char **line)
{
	char	*res;
	ssize_t	r;
	int		ret;

	if (!line)
		return (-1);
	r = gnl_read_to_res(fd, &res);
	ret = gnl_handle_error_and_eof(line, res, r);
	if (ret != 2)
		return (ret);
	return (gnl_assign_line(line, res));
}
