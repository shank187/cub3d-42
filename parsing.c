/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:08 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/25 11:45:14 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	store_map_infos(t_game *game, int map_part, char *line)
{
	if (!ft_strncmp(line, "NO ", 3) && !game->textures.no && \
			ft_strchr(line, '.'))
		game->textures.no = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "SO ", 3) && !game->textures.so && \
			ft_strchr(line, '.'))
		game->textures.so = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "WE ", 3) && !game->textures.we && \
			ft_strchr(line, '.'))
		game->textures.we = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "EA ", 3) && !game->textures.ea && \
			ft_strchr(line, '.'))
		game->textures.ea = ft_strdup(ft_strchr(line, '.'), game);
	else if (!ft_strncmp(line, "F ", 2) && game->floor_color == -1)
		game->floor_color = parse_color_rgb(line);
	else if (!ft_strncmp(line, "C ", 2) && game->ceiling_color == -1)
		game->ceiling_color = parse_color_rgb(line);
	else
		return (0);
	return (1);
}

void	*extract_and_store_data(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		j;
	int		map_part;
	char	*map;
	char	*map_arr;
	char	*tmp;

	map_part = 0;
	line = get_next_line(fd, game);
	map = NULL;
	while (line)
	{
		if (!map_part && !ft_strncmp("\n", line, 13))
		{
			free(line);
			line = get_next_line(fd, game);
			continue ;
		}
		else if (ft_strncmp("\n", line, 13) && !map_part && game->textures.ea \
				&& game->textures.no && game->textures.so && game->textures.we \
				&& game->ceiling_color != -1 && game->floor_color != -1)
			map_part = 1;
		if (!map_part && ft_strncmp("\n", line, 13))
		{
			if (!store_map_infos(game, map_part, line))
				return (free(line), ft_putstr_fd("Error\nINCOMPLET | INCORRECT INFOS.\n", 2), NULL);
		}
		else if (map_part && ft_strncmp("\n", line, 13) && line)
		{
			tmp = map;
			map = ft_strjoin(map, line, game);
			free(tmp);  
		}
		else
			return (free(line), ft_putstr_fd("Error\nINCOMPLET | INCORRECT INFOS.\n", 2), NULL);
		free(line);
		line = get_next_line(fd, game);
	}
	game->map.grid = parse_map(map, game);
	if(!game->map.grid)
		return (ft_putstr_fd("Error\nINVALID MAP!!.\n", 2), NULL);
	return(game);
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

void init_my_struct(t_game *game)
{
	game->ceiling_color = -1;
	game->floor_color = -1;
	game->player.angle = -1;
	game->player.dir = 0;
	game->player.x = -1;
	game->player.y = -1;
	game->map.grid = NULL;
	game->map.is_valid = 1;
	game->textures.no = NULL;
	game->textures.so = NULL;
	game->textures.we = NULL;
	game->textures.ea = NULL;
}

void extract_rgb_from_uint32(unsigned int color)
{
	int i = 16;
	int holder;
	unsigned char c;

	while(i >= 0)
	{
		holder = color;
		holder = holder >> i;
		c = (char) holder;
		printf("|%i|", c);
		i -= 8;
	}
	printf("\n");
}


void clean_data(t_game *game)
{
	ft_replace_chr(game->textures.no, NULL, '\n', 0);
	ft_replace_chr(game->textures.so, NULL, '\n', 0);
	ft_replace_chr(game->textures.we, NULL, '\n', 0);
	ft_replace_chr(game->textures.ea, NULL, '\n', 0);
	ft_replace_chr(game->textures.no, NULL, ' ', 0);
	ft_replace_chr(game->textures.so, NULL, ' ', 0);
	ft_replace_chr(game->textures.we, NULL, ' ', 0);
	ft_replace_chr(game->textures.ea, NULL, ' ', 0);
	ft_replace_chr(NULL, game->map.grid, 'x', '0');
}

void show_data_strored(t_game *game)
{

	printf("player initial pos x = %f | y = %f\nplayer initial dir %c\nplayer angle %f\n", game->player.x, game->player.y, game->player.dir, game->player.angle);
	printf("\nnorth texture |%s|\n", game->textures.no);
	printf("south texture |%s|\n", game->textures.so);
	printf("west texture |%s|\n", game->textures.we);
	printf("east texture |%s|\n\n", game->textures.ea);
	int  i = -1;
	while(game->map.grid[++i])
	{
		printf("|%s|\n", game->map.grid[i]);
	}
	printf("\nceiling color as unsigned int : (%u) & bytes => ", game->ceiling_color);
	extract_rgb_from_uint32(game->ceiling_color);
	printf("floor color as unsigned int : (%u) & bytes => ", game->floor_color);
	extract_rgb_from_uint32(game->floor_color);
}


int parse_inputs(t_game *game, int ac, char **av)
{
	int				fd;
	unsigned int	i;

	init_my_struct(game);
	if (ac != 2)
	{
		ft_putstr_fd("Error\nplease provide a valid scene description file \
with the .cub extension as first argument.\n", 2);
		return (0);
	}
	if (!is_valid_extension(av[1], ".cub"))
		return (ft_putstr_fd("INVALID .cub extension.\n", 2), 0);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		return (ft_putstr_fd("Error\nInvalid file.\n", 2), 0);
	if(extract_and_store_data(fd, game))
		return (clean_data(game), 1);
	return (0);
}

void clean_parsing_stuff(t_game *game)
{
	int i;
	free(game->textures.ea);
	free(game->textures.so);
	free(game->textures.no);
	free(game->textures.we);
	i = -1;
	while(game->map.grid && game->map.grid[++i])
	{
		free(game->map.grid[i]);
	}
	free(game->map.grid);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (parse_inputs(&game, ac, av))
		show_data_strored(&game);
	else
		return(0);
	return (0);
}
