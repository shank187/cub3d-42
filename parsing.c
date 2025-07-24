/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 11:25:08 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/23 13:01:28 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

unsigned int	parse_color_rgb(char *line)
{
	int				i;
	unsigned int	color;
	int				n;
	int				bytes;

	i = 1;
	bytes = 3;
	color = 0;
	while (bytes)
	{
		while (line[i] == ' ')
			i++;
		n = ft_atoi(line, &i);
		printf("atoi %i\n", n);
		if (n > 0)
			 color  = (color << 8) | n;
		else
			return (-1);
		bytes--;
		while (line[i] == ' ' && bytes)
			i++;
		if (line[i] != ',' && bytes)
			return (-1);
		else if (line[i])
			i++;
	}
	while (line[i] == ' ')
		i++;
	if (line[i] != '\0')
		return (-1);
	return (color);
}

int	store_map_infos(t_game *game, int map_part, char *line)
{
	if (!(map_part))
	{
		if (!ft_strncmp(line, "NO ", 3) && !game->textures.no && \
				ft_strchr(line, '.'))
			game->textures.no = ft_strdup(ft_strchr(line, '.'));
		else if (!ft_strncmp(line, "SO ", 3) && !game->textures.so && \
				ft_strchr(line, '.'))
			game->textures.so = ft_strdup(ft_strchr(line, '.'));
		else if (!ft_strncmp(line, "WE ", 3) && !game->textures.we && \
				ft_strchr(line, '.'))
			game->textures.we = ft_strdup(ft_strchr(line, '.'));
		else if (!ft_strncmp(line, "EA ", 3) && !game->textures.ea && \
				ft_strchr(line, '.'))
			game->textures.ea = ft_strdup(ft_strchr(line, '.'));
		else if (!ft_strncmp(line, "F ", 13) && game->ceiling_color != -1)
			game->floor_color = parse_color_rgb(line);
		else if (!ft_strncmp(line, "C ", 13) && game->floor_color != -1)
			game->ceiling_color = parse_color_rgb(line);
		else
			return (0);
	}
	return (1);
}
void find_angle(t_game *game)
{
	if (game->player.dir == "N")
		game->player.angle = M_PI_2 * 3;
	if (game->player.dir == "S")
		game->player.angle = M_PI_2;
	if (game->player.dir == "E")
		game->player.angle = 0;
	if (game->player.dir == "W")
		game->player.angle = M_PI;
}

char	**parse_map(char *str, t_game *game)
{
	int	i;
	int	j;
	int	found;
	char **map_2d;
	int valid;

	game->player.dir = 0;
	i = 0;
	found = 0;
	while (str[i] == '1' || str[i] == '0' || str[i] == '\n' || str[i] == ' ' \
	|| str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
	{
		if(str[i] == ' ')
			str[i] = '1';
		if (!game->player.dir && (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W'))
			game->player.dir = str[i];
		else if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			return NULL;
		i++;
	}
	if (str[i] || !game->player.dir)
		return (NULL);
	map_2d = ft_split(str, '\n');
	i = 0;
	while(map_2d[i] && !found)
	{
		j = 0;
		while(map_2d[i][j])
		{
			if (map_2d[i][j] == 'N' || map_2d[i][j] == 'S' || map_2d[i][j] == 'E' || map_2d[i][j] == 'W')
			{				
				found = 1;
				break;
			}
			if(!found)
				j++;
		}
		if(!found)
			i++;
	}
	map_2d[i][j] = '0';
	game->player.x = j + 0.5;
	game->player.y = i + 0.5;
	flood_walls_check(map_2d, i, j, game);
	find_angle(game);
	if(!game->map.is_valid)
		return (NULL);
	return (map_2d);
}

void	*extract_data(int fd, t_game *game)
{
	char	*line;
	int		i;
	int		j;
	int		map_part;
	char	*map;
	char	*map_arr;
	char	*tmp;

	map_part = 0;
	line = get_next_line(fd);
	map = NULL;
	while (line)
	{
		if (!map_part && !ft_strncmp("\n", line, 13))
			continue ;
		else if (ft_strncmp("\n", line, 13) && !map_part && game->textures.ea \
				&& game->textures.no && game->textures.so && game->textures.we \
				&& game->ceiling_color != -1 && game->floor_color != -1)
			map_part = 1;
		else if (!map_part && ft_strncmp("\n", line, 13))
			if (!store_map_infos(game, map_part, line))
				return (free(line), NULL);
		else if (!map_part && ft_strncmp("\n", line, 13) && line)
		{
			tmp = map;
			map = ft_strjoin(map, line);
			free(tmp);  
		}
		else
			return (free(line), NULL);
		free(line);
		line = get_next_line(fd);
	}
	map_arr = parse_map(map, game);
	if(!map_arr)
		return (NULL);
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

int	main(int ac, char **av)
{
	int				fd;
	t_game			game;
	unsigned int	i;

	init_my_struct(&game);
	if (ac != 2)
	{
		ft_putstr_fd("Error\nplease provide a valid scene description file \
				with the .cub extension as first argument.\n", 2);
		return (1);
	}
	i = parse_color_rgb(av[1]);
	printf("%i \n", i);
	// if (!is_valid_extension(av[1], ".cub"))
	// {
	// 	ft_putstr_fd("not valid .cub extension\n", 2);
	// 	return (1);
	// }
	// fd = open(av[1], O_RDONLY);
	// if (fd == -1)
	// {
	// 	ft_putstr_fd("Error\nInvalid file\n", 2);
	// 	return (1);
	// }
}
