/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 19:36:32 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/11 19:50:07 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <mlx.h>
# include "parse.h"

# define FOV 60
# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 900
# define ROT_SPEED 0.7
# define MOV_SPEED 5
# define TILE_SIZE 64

enum e_keys_events
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_DESTROY = 17,
	LEFT_ARROW_KEY = 123,
	RIGHT_ARROW_KEY = 124,
	A_KEY = 0,
	W_KEY = 13,
	S_KEY = 1,
	D_KEY = 2,
	ESC_KEY = 53
};

enum e_directions
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

typedef struct s_key_pressed
{
	int	left_arrow;
	int	right_arrow;
	int	w;
	int	s;
	int	a;
	int	d;
}	t_key_press;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
}	t_img;

typedef struct s_player
{
	double	x;
	double	y;
	double	angle;
}	t_player;

typedef struct s_ray
{
	double	distance;
	double	angle;
	int		direction;
	double	wall_x;
}	t_ray;

typedef struct s_game_data
{
	void			*mlx;
	void			*mlx_win;
	char			**map;
	t_player		player;
	t_img			img;
	t_map			*t_map;
	double			tile_size;
	int				map_width;
	int				map_height;
	unsigned int	floor_color;
	unsigned int	ceil_color;
	t_key_press		key_event;
	t_img			north_tex;
	t_img			south_tex;
	t_img			west_tex;
	t_img			east_tex;
}	t_game_data;

typedef struct s_dda
{
	double	xr;
	double	yr;
	double	xp;
	double	yp;
	double	step_x;
	double	step_y;
}	t_dda;

void			init_game(t_game_data *g, t_map m);
int				get_rgb_color(int colors[3]);
void			exit_clean_game(t_game_data *game_data, int exit_code);
int				on_key_down(int key, t_game_data *game_data);
int				on_key_up(int key, t_game_data *game_data);
int				on_destroy(t_game_data *game_data);
void			player_movs(t_game_data *game_data);
void			dda(t_game_data *g, t_ray *r);
int				render(t_game_data *g);
unsigned int	get_pixel_color(t_img *img, int x, int y);
void			put_pixel(t_img *img, int x, int y, unsigned int color);

#endif