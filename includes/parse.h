/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 09:34:09 by elben-id          #+#    #+#             */
/*   Updated: 2025/11/11 19:28:22 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

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

int		parse_cub_file(char *filename, t_map *map);

int		parse_color_line(char *line, int *color);
int		parse_identifier_line(char *line, t_map *map);
int		parse_identifier_line2(char *line, t_map *map);

int		validate_map(t_map *map);

int		is_allowed(char c);
int		scan_row_for_player(t_map *map, int y);
int		locate_player(t_map *map);
int		cell_is_enclosed(t_map *map, int x, int y);
void	fill_spaces_with_walls(t_map *map);

t_line	*read_file_to_list(char *filename);
int		build_grid_from_list(t_line *start, t_map *map);
void	free_list(t_line *head);
void	free_map(t_map *map);
void	print_error(char *message);

size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
char	*ft_strrchr(char *s, int c);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi_simple(char *s);
void	ft_bzero(void *s, size_t n);

int		is_empty_line(char *text);
t_line	*consume_identifiers(t_line *head, t_map *map);
t_line	*skip_empty_lines(t_line *cur);

int		get_next_line(int fd, char **line);

char	*append_char(char *buf, char c);

#endif