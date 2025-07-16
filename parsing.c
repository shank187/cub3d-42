/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:08 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/16 16:06:17 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	store_to_memory(t_game *game, int *map_part, char *line)
{
	if (!(*map_part))
	{
		if (!ft_strncmp(line, "NO ", 3))
			;
		else if (!ft_strncmp(line, "SO ", 3))
			;
		else if (!ft_strncmp(line, "WE ", 3))
			;
		else if (!ft_strncmp(line, "EA ", 3))
			;
		else
			return (0);
	}
	else
	{

	}
}

void	*extract_data(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		map_part;

	map_part = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!map_part && !ft_strncmp("\n", line, 13))
			continue ;
		else
		{
			
		}
	}
}

int	is_valid_extension(char *filename, char *identifier)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	i = ft_strlen(identifier);
	j = ft_strlen(filename);
	k = 0;
	while (identifier[k] && filename[j - i] && \
			identifier[k++] == filename[j++ - i])
		;
	return (!filename[j - i]);
}

int	main(int ac, char **av)
{
	int		fd;
	t_game	game;

	if (ac != 2)
	{
		ft_putstr_fd("Error\nplease provide a valid scene description file \
				with the .cub extension as first argument.\n", 2);
		return (1);
	}
	if (!is_valid_extension(av[1], ".cub"))
	{
		ft_putstr_fd("not valid .cub extension\n", 2);
		return (1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nInvalid file\n", 2);
		return (1);
	}
}
