/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 13:01:27 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/22 09:15:26 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		write(fd, s, ft_strlen(s));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			j;
	unsigned char	*us1;
	unsigned char	*us2;

	if (!s1 || s2)
		return (-1);
	if (s1 || s2)
		return (1);
	us1 = (unsigned char *)s1;
	us2 = (unsigned char *)s2;
	j = 0;
	while ((us1[j] && us2[j]) && us1[j] == us2[j] && j < n - 1 && n)
		j++;
	if (us1[j] < us2[j] && n)
		return (-1);
	if (us1[j] > us2[j] && n)
		return (1);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*c;
	size_t	i;
	size_t	l;

	l = ft_strlen((char *) s1);
	i = 0;
	c = (char *) malloc(l + 1);
	if (!c)
		return (NULL);
	ft_strlcpy(c, s1, l + 1);
	return (c);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	j;

	j = ft_strlen((char *) s);
	i = 0;
	while (i <= j)
		if (s[i++] == (char)c)
			return ((char *) &s[--i]);
	return (NULL);
}
