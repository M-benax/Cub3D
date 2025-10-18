/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 10:44:34 by M-benax           #+#    #+#             */
/*   Updated: 2025/10/18 12:46:07 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <errno.h>
# include <mlx.h>

# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 600
# define TEXTURE_SIZE 64
# define GNL_BUFFER 1024

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}	t_img;

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
	t_img	textures[4];
	int		player_x;
	int		player_y;
	char	player_dir;
	/* identifier presence flags (set to 1 when parsed) */
	int		no_set;
	int		so_set;
	int		we_set;
	int		ea_set;
	int		f_set;
	int		c_set;
}	t_map;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	t_img	img;
	t_map	*map;
}	t_game;

/* init.c */
int		init_game(t_game *game);
int		init_window(t_game *game);

/* parser.c */
int		parse_cub_file(char *filename, t_map *map);
int		validate_map(t_map *map);

/* textures.c */
int		load_textures(t_game *game);
void	free_textures(t_game *game);

/* utils.c */
void	free_map(t_map *map);
void	error_exit(char *message);
int		create_rgb(int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/* events.c */
int		key_press(int keycode, t_game *game);
int		close_window(t_game *game);

/* helpers.c */
size_t	ft_strlen(char *s);
char	*ft_strdup(char *s1);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_atoi_simple(char *s);
void	ft_bzero(void *s, size_t n);

/* get_next_line.c */
int		get_next_line(int fd, char **line);

#endif