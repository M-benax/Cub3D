/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_ray_cast.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:19:37 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/02 00:54:51 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_dda_v(t_game_data *g, t_ray *r, t_dda *d)
{
	d->xp = g->player.x;
	d->yp = g->player.y;
	d->xr = floor(d->xp / TILE_SIZE) * TILE_SIZE;
	if (cos(r->angle) > 0)
		d->xr += TILE_SIZE;
	else
		d->xr -= 1e-10;
	d->yr = d->yp + (d->xr - d->xp) * tan(r->angle);
	if (cos(r->angle) > 0)
		d->step_x = TILE_SIZE;
	else
		d->step_x = -TILE_SIZE;
	d->step_y = d->step_x * tan(r->angle);
}

void	dda_v(t_game_data *g, t_ray *r)
{
	t_dda	d;

	init_dda_v(g, r, &d);
	while (1)
	{
		r->distance = sqrt((d.xr - d.xp)
				* (d.xr - d.xp) + (d.yr - d.yp) * (d.yr - (d.yp)));
		r->wall_x = (d.yr - floor(d.yr / TILE_SIZE) * TILE_SIZE) / TILE_SIZE;
		if (d.xr < 0 || d.yr < 0 || d.yr >= g->map_height * TILE_SIZE
			|| d.xr >= g->map_width * TILE_SIZE
			|| g->map[(int)d.yr / TILE_SIZE][(int)d.xr / TILE_SIZE] == '1')
			break ;
		d.xr += d.step_x;
		d.yr += d.step_y;
	}
}

void	init_dda_h(t_game_data *g, t_ray *r, t_dda *d)
{
	d->xp = g->player.x;
	d->yp = g->player.y;
	d->yr = floor(d->yp / TILE_SIZE) * TILE_SIZE;
	if (sin(r->angle) > 0)
		d->yr += TILE_SIZE;
	else
		d->yr -= 1e-10;
	d->xr = d->xp + (d->yr - d->yp) / tan(r->angle);
	d->step_y = -TILE_SIZE;
	if (sin(r->angle) > 0)
		d->step_y = TILE_SIZE;
	d->step_x = d->step_y / tan(r->angle);
}

void	dda_h(t_game_data *g, t_ray *r)
{
	t_dda	d;

	init_dda_h(g, r, &d);
	while (1)
	{
		r->distance = sqrt((d.xr - d.xp)
				* (d.xr - d.xp) + (d.yr - d.yp) * (d.yr - (d.yp)));
		r->wall_x = (d.xr - floor(d.xr / TILE_SIZE) * TILE_SIZE) / TILE_SIZE;
		if (d.yr < 0 || d.xr < 0 || d.yr >= g->map_height * TILE_SIZE
			|| d.xr >= g->map_width * TILE_SIZE
			|| g->map[(int)d.yr / TILE_SIZE][(int)d.xr / TILE_SIZE] == '1')
			break ;
		d.xr += d.step_x;
		d.yr += d.step_y;
	}
}

void	dda(t_game_data *g, t_ray *r)
{
	t_ray	v_hit;
	t_ray	h_hit;

	h_hit.angle = r->angle;
	v_hit.angle = r->angle;
	dda_h(g, &h_hit);
	dda_v(g, &v_hit);
	if (v_hit.distance < h_hit.distance)
	{
		r->distance = v_hit.distance;
		r->wall_x = v_hit.wall_x;
		if (cos(r->angle) > 0)
			r->direction = EAST;
		else
			r->direction = WEST;
	}
	else
	{
		r->distance = h_hit.distance;
		r->wall_x = h_hit.wall_x;
		if (sin(r->angle) > 0)
			r->direction = NORTH;
		else
			r->direction = SOUTH;
	}
}
