/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:20:51 by elben-id          #+#    #+#             */
/*   Updated: 2025/11/14 19:52:15 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (i < n && (s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

int	ft_atoi_simple(char *s)
{
	int	neg;
	int	val;

	if (!s)
		return (0);
	neg = 1;
	val = 0;
	while (*s == ' ' || *s == '\t')
		s++;
	if (*s == '-')
		neg = -1;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		val = val * 10 + (*s - '0');
		s++;
	}
	return (val * neg);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*p;

	p = (char *)s;
	i = 0;
	while (i < n)
	{
		p[i] = 0;
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
