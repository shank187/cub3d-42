/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:28:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/26 11:01:03 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_strlen_chr(char *str, char chr)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && str[i] != chr)
		i++;
	return (i);
}

static int	init_gnl(char **str, t_game *game)
{
	if (!(*str))
	{
		*str = malloc(BUFFER_SIZE + 1);
		if (!*str)
		{
			clean_parsing_stuff(game);
			exit(1);
		}
		(*str)[0] = '\0';
	}
	return (1);
}

static int	read_and_append(int fd, char **str, char *line, t_game *game)
{
	char	*tmp;
	int		read_size;

	read_size = read(fd, line, BUFFER_SIZE);
	while (read_size > 0)
	{
		line[read_size] = '\0';
		tmp = *str;
		*str = ft_strjoin(*str, line, game);
		free(tmp);
		if (ft_strchr(*str, '\n'))
			break ;
		read_size = read(fd, line, BUFFER_SIZE);
	}
	return (read_size);
}

static char	*extract_line(char **str, char *line, t_game *game)
{
	char	*tmp;

	tmp = line;
	line = ft_substr(*str, 0, ft_strlen_chr(*str, '\n') + 1, game);
	free(tmp);
	tmp = *str;
	if (ft_strchr(*str, '\n'))
		*str = ft_strdup(ft_strchr(*str, '\n') + 1, game);
	else
		*str = NULL;
	free(tmp);
	return (line);
}

char	*get_next_line(int fd, t_game *game)
{
	static char	*str;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!init_gnl(&str, game))
		return (NULL);
	line = malloc(BUFFER_SIZE + 1);
	if (!line)
		return (NULL);
	if (read(fd, line, 0) < 0)
	{
		free(line);
		free(str);
		str = NULL;
		clean_parsing_stuff(game);
		exit(1);
	}
	if (read_and_append(fd, &str, line, game) >= 0 && str && str[0])
		return (extract_line(&str, line, game));
	free(line);
	return (NULL);
}
