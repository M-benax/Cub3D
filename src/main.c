/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elben-id <elben-id@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:32:23 by elben-id          #+#    #+#             */
/*   Updated: 2025/11/11 15:25:06 by elben-id         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_map	map;

	check_args(argc, argv);
	ft_bzero(&map, sizeof(map));
	if (!parse_cub_file(argv[1], &map))
	{
		printf("Error\nInvalid map file\n");
		free_map(&map);
		return (1);
	}
	printf("Parsed OK\n");
	int y = 0;
	while (y < map.height)
	{
		printf("%s\n", map.grid[y]);
		y++;
	}
	free_map(&map);
	return (0);
}
