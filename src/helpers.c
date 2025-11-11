/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:31:42 by elben-id          #+#    #+#             */
/*   Updated: 2025/11/11 15:19:46 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*alloc_empty(void)
{
	char	*dst;

	dst = malloc(1);
	if (!dst)
		return (NULL);
	dst[0] = '\0';
	return (dst);
}

static char	*copy_range(char *s, size_t start, size_t len)
{
	char	*dst;
	size_t	i;

	dst = malloc(len + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = s[start + i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strdup(char *s1)
{
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	start = 0;
	while (s1[start] == ' ' || s1[start] == '\t')
		start++;
	if (s1[start] == '\0')
		return (alloc_empty());
	end = ft_strlen(s1) - 1;
	while (end > start && (s1[end] == ' ' || s1[end] == '\t'))
		end--;
	return (copy_range(s1, start, end - start + 1));
}
