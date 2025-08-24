/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 10:23:23 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/24 13:24:02 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	ft_replace_chr(char *s, char **as, char target, char new_chr)
{
	int	i;
	int	j;

	i = -1;
	while (s && s[++i])
		if (s[i] == target)
			s[i] = new_chr;
	j = -1;
	while (as && as[++j])
	{
		i = -1;
		while (as[j] && as[j][++i])
			if (as[j][i] == target)
				as[j][i] = new_chr;
	}
}

void	free_2d_arr(char **str)
{
	int	i;

	i = -1;
	while (str && str[++i])
		free(str[i]);
	if (str)
		free(str);
}
