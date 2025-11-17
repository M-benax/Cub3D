/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:39:24 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/11 19:48:34 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static unsigned int	get_wall_color(t_ray *r, double factor, t_game_data *g)
{
	if (r->direction == NORTH)
		return (get_pixel_color(&g->north_tex, (1 - r->wall_x) * g->north_tex.w,
				(factor * g->north_tex.h)));
	if (r->direction == SOUTH)
		return (get_pixel_color(&g->south_tex, r->wall_x * g->south_tex.w,
				(factor * g->south_tex.h)));
	if (r->direction == WEST)
		return (get_pixel_color(&g->west_tex, (1 - r->wall_x) * g->west_tex.w,
				(factor * g->west_tex.h)));
	return (get_pixel_color(&g->east_tex, r->wall_x * g->east_tex.w,
			(factor * g->east_tex.h)));
}

static void	draw_floor_ceiling(int start, int end, t_game_data *g, int x)
{
	while (start >= 0)
	{
		put_pixel(&g->img, x, start, g->ceil_color);
		start--;
	}
	while (end < WINDOW_HEIGHT)
	{
		put_pixel(&g->img, x, end, g->floor_color);
		end++;
	}
}

static void	draw_wall(t_game_data *g, t_ray *ray, int i)
{
	double	factor;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		wall_s;

	line_height = (int)(((WINDOW_WIDTH / (2 * tan(FOV / 2 * M_PI / 180))))
			* TILE_SIZE) / (ray->distance * cos(-ray->angle + g->player.angle));
	draw_start = WINDOW_HEIGHT / 2 - line_height / 2;
	wall_s = draw_start;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + WINDOW_HEIGHT / 2;
	if (draw_end >= WINDOW_HEIGHT)
		draw_end = WINDOW_HEIGHT - 1;
	draw_floor_ceiling(draw_start, draw_end, g, i);
	while (draw_start <= draw_end)
	{
		factor = (double)(draw_start - wall_s) / (line_height);
		put_pixel(&g->img, i, draw_start, get_wall_color(ray, factor, g));
		draw_start++;
	}
}

static void	cast_rays(t_game_data *g)
{
	int		i;
	t_ray	r;

	r.angle = g->player.angle - ((FOV * M_PI / 180) / 2);
	i = 0;
	while (i < WINDOW_WIDTH)
	{
		r.angle += (FOV * M_PI / 180) / WINDOW_WIDTH;
		dda(g, &r);
		draw_wall(g, &r, i);
		i++;
	}
}

int	render(t_game_data *g)
{
	cast_rays(g);
	mlx_put_image_to_window(g->mlx, g->mlx_win, g->img.img, 0, 0);
	player_movs(g);
	return (0);
}
