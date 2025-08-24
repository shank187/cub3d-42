/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:08 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/24 13:24:14 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

int	parse_inputs(t_game *game, int ac, char **av)
{
	int				fd;

	init_my_struct(game);
	if (ac != 2)
	{
		ft_putstr_fd("Error\nplease provide a valid scene description file \
with the .cub extension as first argument.\n", 2);
		return (0);
	}
	if (!is_valid_extension(av[1], ".cub"))
		return (ft_putstr_fd("Error\nINVALID .cub extension.\n", 2), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nInvalid file.\n", 2), 0);
	if (extract_and_store_data(fd, game))
		return (clean_data(game), 1);
	return (0);
}

int	init_p_d_ns(t_game *game)
{
	if (game->player.dir == 'S')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = 1.0;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0.0;
		return (1);
	}
	else if (game->player.dir == 'N')
	{
		game->player.dir_x = 0.0;
		game->player.dir_y = -1.0;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0.0;
		return (1);
	}
	return (0);
}

void	init_player_direction(t_game *game)
{
	int	a;

	a = init_p_d_ns(game);
	if (game->player.dir == 'W' && a == 0)
	{
		game->player.dir_x = 1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = -0.66;
	}
	else if (game->player.dir == 'E' && a == 0)
	{
		game->player.dir_x = -1.0;
		game->player.dir_y = 0.0;
		game->player.plane_x = 0.0;
		game->player.plane_y = 0.66;
	}
}

// void    leaks(void)
// {
//     system("leaks cub3D");
// }

void f();
int	main(int ac, char **av)
{
	t_game	game;

	atexit(f);
	ft_memset(&game, 0, sizeof(game));
	if (parse_inputs(&game, ac, av))
		show_data_strored(&game);
	else
		return (1);
	init_game(&game);
	game.map_h = map_h(game.map);
	game.map_w = map_w(game.map);
	init_player_direction(&game);
	load_texs(&game);
	raycast(&game);
	mini_map(&game);
	render_horse_sprite(&game);
	mlx_put_image_to_window(game.mlx, game.win, game.img.img, 0, 0);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game);
	mlx_hook(game.win, 6, (1L << 6), mouse_move, &game);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx, game_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}

void f()
{
	system("leaks -q cub3D");
}