/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:23:52 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/11 19:30:10 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_player_angle(char dir, t_game_data *g)
{
	if (dir == 'N')
		g->player.angle = -M_PI_2;
	if (dir == 'S')
		g->player.angle = M_PI_2;
	if (dir == 'E')
		g->player.angle = 0;
	if (dir == 'W')
		g->player.angle = M_PI;
}

static void	error_loading_textures(t_game_data *g, char *tex_path)
{
	print_error("Cannot open the texture <");
	write(2, tex_path, ft_strlen(tex_path));
	write(2, ">\n", 2);
	exit_clean_game(g, 1);
}

static void	load_textures_2(t_game_data *g)
{
	t_map	*m;

	m = g->t_map;
	g->south_tex.img = mlx_xpm_file_to_image(g->mlx, m->so_path,
			&g->south_tex.w, &g->south_tex.h);
	if (!g->south_tex.img)
		error_loading_textures(g, m->so_path);
	g->south_tex.addr = mlx_get_data_addr(g->south_tex.img,
			&g->south_tex.bits_per_pixel,
			&g->south_tex.line_length, &g->south_tex.endian);
	g->west_tex.img = mlx_xpm_file_to_image(g->mlx, m->we_path,
			&g->west_tex.w, &g->west_tex.h);
	if (!g->west_tex.img)
		error_loading_textures(g, m->we_path);
	g->west_tex.addr = mlx_get_data_addr(g->west_tex.img,
			&g->west_tex.bits_per_pixel,
			&g->west_tex.line_length, &g->west_tex.endian);
}

static void	load_textures(t_game_data *g)
{
	t_map	*m;

	m = g->t_map;
	g->north_tex.img = mlx_xpm_file_to_image(g->mlx, m->no_path,
			&g->north_tex.w, &g->north_tex.h);
	if (!g->north_tex.img)
		error_loading_textures(g, m->no_path);
	g->north_tex.addr = mlx_get_data_addr(g->north_tex.img,
			&g->north_tex.bits_per_pixel,
			&g->north_tex.line_length, &g->north_tex.endian);
	g->east_tex.img = mlx_xpm_file_to_image(g->mlx, m->ea_path,
			&g->east_tex.w, &g->east_tex.h);
	if (!g->east_tex.img)
		error_loading_textures(g, m->ea_path);
	g->east_tex.addr = mlx_get_data_addr(g->east_tex.img,
			&g->east_tex.bits_per_pixel,
			&g->east_tex.line_length, &g->east_tex.endian);
	load_textures_2(g);
}

void	init_game(t_game_data *g, t_map m)
{
	g->map_height = m.height;
	g->map_width = m.width;
	g->player.x = TILE_SIZE * m.player_x + TILE_SIZE / 2;
	g->player.y = TILE_SIZE * m.player_y + TILE_SIZE / 2;
	g->map = m.grid;
	g->t_map = &m;
	set_player_angle(m.player_dir, g);
	g->floor_color = get_rgb_color(m.floor_color);
	g->ceil_color = get_rgb_color(m.ceiling_color);
	g->img.img = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!g->img.img)
		exit_clean_game(g, 1);
	g->img.addr = mlx_get_data_addr(g->img.img, &g->img.bits_per_pixel,
			&g->img.line_length, &g->img.endian);
	load_textures(g);
}
