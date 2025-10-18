
#include "../includes/cub3d.h"

int	key_press(int keycode, t_game *game)
{
	(void)game;
	if (keycode == 53)
	{
		exit(0);
	}
	return (0);
}

int	close_window(t_game *game)
{
	(void)game;
	exit(0);
	return (0);
}