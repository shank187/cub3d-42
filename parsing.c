/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:08 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/26 10:46:54 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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

int	main(int ac, char **av)
{
	t_game	game;

	if (parse_inputs(&game, ac, av))
		show_data_strored(&game);
	else
		return (1);
	return (0);
}
