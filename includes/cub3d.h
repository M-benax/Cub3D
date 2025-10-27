/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:34:09 by elben-id          #+#    #+#             */
/*   Updated: 2025/10/25 09:34:12 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <errno.h>

typedef struct s_line
{
	char			*text;
	struct s_line	*next;
}	t_line;

typedef struct s_map
{
	char	**grid;
	int		width;
	int		height;
	char	*no_path;
	char	*so_path;
	char	*we_path;
	char	*ea_path;
	int		floor_color[3];
	int		ceiling_color[3];
	int		player_x;
	int		player_y;
	char	player_dir;
	int		no_set;
	int		so_set;
	int		we_set;
	int		ea_set;
	int		f_set;
	int		c_set;
}	t_map;

/* parser: main entry */
int		parse_cub_file(char *filename, t_map *map);

/* parser helpers exported across parser files */
int		parse_color_line(char *line, int *color);
int		parse_identifier_line(char *line, t_map *map);
int		parse_identifier_line2(char *line, t_map *map);

/* validate.c */
int		validate_map(t_map *map);

/* utils.c */
t_line	*read_file_to_list(char *filename);
int		build_grid_from_list(t_line *start, t_map *map);
void	free_list(t_line *head);
void	free_map(t_map *map);
void	error_exit(char *message);

/* helpers.c */
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi_simple(char *s);
void	ft_bzero(void *s, size_t n);

/* get_next_line.c */
int		get_next_line(int fd, char **line);

/* gnl utility (append helper) */
char	*append_char(char *buf, char c);

#endif