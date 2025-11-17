/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:00:00 by M-benax           #+#    #+#             */
/*   Updated: 2025/10/31 13:55:21 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static int	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	parse_component(char **pp, int *out)
{
	char	*p;
	int		len;
	long	val;

	p = *pp;
	if (!is_digit(*p))
		return (0);
	len = 0;
	while (is_digit(p[len]))
		len++;
	if (len > 3)
		return (0);
	val = ft_atoi_simple(p);
	if (val < 0 || val > 255)
		return (0);
	*out = (int)val;
	*pp = p + len;
	return (1);
}

static int	check_trailing(char *p)
{
	while (*p == ' ' || *p == '\t')
		p++;
	if (*p != '\0')
		return (0);
	return (1);
}

int	parse_color_line(char *line, int *color)
{
	char	*p;
	int		i;
	int		val;

	if (!line || !color)
		return (0);
	p = line;
	i = 0;
	while (i < 2)
	{
		if (!parse_component(&p, &val))
			return (0);
		color[i] = val;
		if (*p != ',')
			return (0);
		p++;
		i++;
	}
	if (!parse_component(&p, &val))
		return (0);
	color[i] = val;
	if (!check_trailing(p))
		return (0);
	return (1);
}
