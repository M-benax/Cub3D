/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_mov.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:36:59 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/04 22:10:44 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	rotate_player(t_player *player, double d_angle)
{
	player->angle += d_angle * ROT_SPEED;
	player->angle = fmod(player->angle, M_PI * 2);
}

static void	move_up_down(t_player *player, int sign, t_game_data *g)
{
	double	new_x;
	double	new_y;

	new_x = player->x + sign * cos(player->angle) * MOV_SPEED;
	new_y = player->y + sign * sin(player->angle) * MOV_SPEED;
	if (g->map[(int)((new_y) / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
		return ;
	player->x = new_x;
	player->y = new_y;
}

static void	move_left_right(t_player *player, int sign, t_game_data *g)
{
	double	new_x;
	double	new_y;

	new_x = player->x + sign * cos(M_PI_2 + player->angle) * MOV_SPEED;
	new_y = player->y + sign * sin(M_PI_2 + player->angle) * MOV_SPEED;
	if (g->map[(int)(new_y / TILE_SIZE)][(int)(new_x / TILE_SIZE)] == '1')
		return ;
	player->x = new_x;
	player->y = new_y;
}

void	player_movs(t_game_data *game_data)
{
	if (game_data->key_event.right_arrow == 1)
		rotate_player(&game_data->player, 0.1);
	if (game_data->key_event.left_arrow == 1)
		rotate_player(&game_data->player, -0.1);
	if (game_data->key_event.w == 1)
		move_up_down(&game_data->player, 1, game_data);
	if (game_data->key_event.s == 1)
		move_up_down(&game_data->player, -1, game_data);
	if (game_data->key_event.a)
		move_left_right(&game_data->player, -1, game_data);
	if (game_data->key_event.d)
		move_left_right(&game_data->player, 1, game_data);
}
