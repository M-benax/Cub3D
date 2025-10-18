
#include "../includes/cub3d.h"

static char	*append_char(char *buf, char c)
{
	size_t	len;
	char	*res;
	size_t	i;

	len = buf ? ft_strlen(buf) : 0;
	res = (char *)malloc(len + 2);
	if (!res)
	{
		if (buf)
			free(buf);
		return (NULL);
	}
	i = 0;
	while (i < len)
	{
		res[i] = buf[i];
		i++;
	}
	res[i++] = c;
	res[i] = '\0';
	if (buf)
		free(buf);
	return (res);
}

int	get_next_line(int fd, char **line)
{
	char	c;
	ssize_t	r;
	char	*res;

	if (!line)
		return (-1);
	res = NULL;
	while ((r = read(fd, &c, 1)) > 0)
	{
		if (c == '\n')
		{
			*line = res ? res : ft_strdup("");
			if (!*line)
				return (-1);
			return (1);
		}
		res = append_char(res, c);
		if (!res)
			return (-1);
	}
	if (r < 0)
	{
		if (res)
			free(res);
		return (-1);
	}
	if (res)
	{
		*line = res;
		return (1);
	}
	*line = NULL;
	return (0);
}