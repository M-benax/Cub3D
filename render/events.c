/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:22:16 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/02 19:30:19 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	on_destroy(t_game_data *game_data)
{
	exit_clean_game(game_data, 0);
	return (1);
}

int	on_key_down(int key, t_game_data *game_data)
{
	if (key == ESC_KEY)
		exit_clean_game(game_data, 0);
	if (key == LEFT_ARROW_KEY)
		game_data->key_event.left_arrow = 1;
	if (key == RIGHT_ARROW_KEY)
		game_data->key_event.right_arrow = 1;
	if (key == A_KEY)
		game_data->key_event.a = 1;
	if (key == W_KEY)
		game_data->key_event.w = 1;
	if (key == D_KEY)
		game_data->key_event.d = 1;
	if (key == S_KEY)
		game_data->key_event.s = 1;
	return (1);
}

int	on_key_up(int key, t_game_data *game_data)
{
	if (key == LEFT_ARROW_KEY)
		game_data->key_event.left_arrow = 0;
	if (key == RIGHT_ARROW_KEY)
		game_data->key_event.right_arrow = 0;
	if (key == A_KEY)
		game_data->key_event.a = 0;
	if (key == W_KEY)
		game_data->key_event.w = 0;
	if (key == D_KEY)
		game_data->key_event.d = 0;
	if (key == S_KEY)
		game_data->key_event.s = 0;
	return (1);
}
