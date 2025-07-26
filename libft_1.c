/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 10:15:11 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/25 12:08:53 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	ft_atoi(const char *str, int *i)
{
	long	t;
	long	oldt;

	t = 0;
	oldt = 0;

	while (str[(*i)] >= '0' && str[(*i)] <= '9')
	{
		t = (t * 10) + (str[(*i)++] - '0');
		if ((t / 10) != oldt)
			return (-1);
		oldt = t;
	}
	if ((str[(*i)] != ' '  &&  str[(*i)] != ',' && str[*i] != '\n' && str[*i] != 0) || t > 255 || t < 0)
		return (-2);
	return ((int)t);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = ft_strlen((char *)src);
	if (!dstsize)
		return (src_len);
	if (!src)
	{
		dst = NULL;
		return (-1);
	}
	while ((i < dstsize - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (src_len);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	if (!dst && !dstsize)
		return (ft_strlen((char *)src));
	if (!src)
	{
		dst = NULL;
		return (-1);
	}
	i = ft_strlen(dst);
	if (dstsize < i + 1)
		return (ft_strlen((char *)src) + dstsize);
	j = 0;
	while ((dstsize > i + 1) && src[j])
		dst[i++] = src[j++];
	dst[i] = 0;
	return (i + ft_strlen((char *)src) - j);
}

char	*ft_strjoin(char const *s1, char const *s2, t_game *game)
{
	size_t	siz;
	char	*c;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	siz = ft_strlen((char *) s1) + ft_strlen((char *) s2) + 1;
	c = (char *) malloc(siz);
	if (!c)
		return (clean_parsing_stuff(game), exit(1), NULL);
	ft_strlcpy(c, s1, ft_strlen((char *) s1) + 1);
	ft_strlcat(c, s2, siz);
	return (c);
}

char	*ft_substr(char const *s, unsigned int start, size_t len, t_game *game)
{
	size_t	s_len;
	char	*c;
	size_t	size;

	if (!s)
		return (NULL);
	s_len = ft_strlen((char *) s);
	if (start > s_len)
		return (ft_strdup("", game));
	s_len = ft_strlen((char *) &s[start]);
	size = len + 1;
	if (s_len < len)
		size = s_len + 1;
	c = (char *) malloc(size);
	if (!c)
		return (clean_parsing_stuff(game), exit(1), NULL);
	ft_strlcpy(c, &s[start], size);
	return (c);
}
