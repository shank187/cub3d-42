/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:28:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/25 11:46:17 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


int ft_strlen_chr(char *str, char chr)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != chr && str[i])
		i++;
	return (i);
}

char *get_next_line(int fd, t_game *game)
{
	static char	*str;
	char		*tmp;
	char		*line;
	int			i;

	i = 0;
	if (!str)
	{
		str = malloc(BUFFER_SIZE + 1);
		if (str)
			str[0] = 0;
		else
			return (clean_parsing_stuff(game) ,exit(1), NULL);
	}
	line = malloc(BUFFER_SIZE + 1);
	if(!line)
		return (free(line), NULL);
	if (read(fd, line, 0) == -1)
		return (free(line), free(str), str = NULL, clean_parsing_stuff(game), exit(1), NULL);
	i = read(fd, line, BUFFER_SIZE);
	while(i)
	{
		line[i] = 0;
		tmp = str;
		str = ft_strjoin(str, line, game);
		free(tmp);
		if (ft_strchr(str, '\n'))
			break;
		i = read(fd, line, BUFFER_SIZE);
	}
	if (str && str[0])
	{
		tmp = line;
		line = ft_substr(str, 0, ft_strlen_chr(str, '\n') + 1, game);
		free(tmp);
		tmp = str;
		if (ft_strchr(str, '\n'))
			str = ft_strdup(ft_strchr(str, '\n') + 1, game);
		else 
			str = NULL;
		free(tmp);
		return (line);
	}
	return (free(line), NULL);
}


// int main(void)
// {
// 	int i = 0;
// 	char *s;
// 	i = open("map.cub", O_RDONLY);
	
// 	s = get_next_line(i);
// 	while(s)
// 	{
// 		printf("%s", s);
// 		s = get_next_line(i);
// 	}
// 	s = get_next_line(i);
// 	printf("%s", s);
// }