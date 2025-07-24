/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 15:28:47 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/24 08:28:26 by aelbour          ###   ########.fr       */
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

char *get_next_line(int fd)
{
	static char	*str;
	char		*tmp;
	char		*line;
	int			i;

	i = 0;
	if (!str)
	{
		str = malloc(BUFFER_SIZE + 1);
		str[0] = 0;
	}
	line = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	if (read(fd, line, 0) == -1)
		return (free(line), free(str), str = NULL, NULL);
	i = read(fd, line, BUFFER_SIZE);
	while(i)
	{
		line[i] = 0;
		tmp = str;
		str = ft_strjoin(str, line);
		free(tmp);
		if (ft_strchr(str, '\n'))
		{
			tmp = line;
			line = ft_substr(str, 0, ft_strlen_chr(str, '\n'));
			free(tmp);
			tmp = str;
			str = ft_substr(str, ft_strlen_chr(str, '\n'), ft_strlen(str));
			free(tmp);
			return(line);
		}
		i = read(fd, line, BUFFER_SIZE);
	}
	if(i == 0 && str && str[i])
	{
		tmp = line;
		line = str;
		free(tmp);
		str = NULL;
		return (line);
	}
	return (NULL);
}


int main(void)
{
	int i = 0;
	char *s;
	i = open("map.cub", O_RDONLY);
	s = get_next_line(i);
	printf("%s", s);
	s = get_next_line(i);
	printf("%s", s);
	s = get_next_line(i);
	printf("%s", s);
}