/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:22:20 by elben-id          #+#    #+#             */
/*   Updated: 2025/10/24 16:22:33 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static char	*copy_and_alloc(char *src, size_t len)
{
	char	*res;
	size_t	i;

	res = (char *)malloc(len + 2);
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = src[i];
		i++;
	}
	return (res);
}

char	*append_char(char *buf, char c)
{
	size_t	len;
	char	*res;
	size_t	i;

	if (buf)
		len = ft_strlen(buf);
	else
		len = 0;
	res = copy_and_alloc(buf, len);
	if (!res)
	{
		if (buf)
			free(buf);
		return (NULL);
	}
	i = len;
	res[i++] = c;
	res[i] = '\0';
	if (buf)
		free(buf);
	return (res);
}
