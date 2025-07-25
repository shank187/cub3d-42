/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 09:53:49 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/25 11:45:56 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	skip_seps(size_t *i, char const *s, char c)
{
	while (s[*i] && s[*i] == c)
		(*i)++;
}

static size_t	count_cols(char const *s, char c)
{
	size_t	t;
	size_t	i;

	t = 0;
	i = 0;
	if (!s[i])
		return (0);
	skip_seps(&i, s, c);
	while (s[i])
	{
		if (s[i] == c)
		{
			skip_seps(&i, s, c);
			t++;
		}
		else
			i++;
	}
	if (s[i - 1] != c)
		t++;
	return (t);
}

static int	check_crash(char **arr, size_t i)
{
	if (!arr[i])
	{
		while (i > 0)
		{
			i--;
			free(arr[i]);
		}
		free(arr);
		return (0);
	}
	return (1);
}

static int	ft_store(char **arr, const char *s, char c, size_t cols, t_game *game)
{
	size_t	i;
	size_t	j;
	size_t	l;

	j = 0;
	i = 0;
	skip_seps(&i, s, c);
	l = i;
	while (j < cols)
	{
		if (s[i] == c || !s[i])
		{
			arr[j] = ft_substr(s, l, i - l, game);
			if (!check_crash(arr, j))
				return (0);
			skip_seps(&i, s, c);
			l = i;
			j++;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c, t_game *game)
{
	size_t	cols;
	char	**arr;

	if (!s)
		return (NULL);
	cols = count_cols(s, c);
	arr = (char **)malloc((cols + 1) * sizeof(char *));
	if (!arr)
		return (clean_parsing_stuff(game), exit(1), NULL);
	arr[cols] = NULL;
	if (cols)
	{
		if (ft_store(arr, s, c, cols, game))
			return (arr);
		else
			return (NULL);
	}
	return (arr);
}