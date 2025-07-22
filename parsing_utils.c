/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:28 by aelbour           #+#    #+#             */
/*   Updated: 2025/07/22 13:36:10 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void flood_fill(char **arr, int i, int j, t_game *game)
{
	if(! game->map.is_valid)
		return;
	printf("%c i = %i | j = %i\n", arr[i][j], i, j);
	arr[i][j] = 'x';
	
	if (arr[i + 1] && arr[i + 1][j] == '0')
		flood_fill(arr, i + 1, j, game);
	else if (arr[i + 1] && arr[i + 1][j] != '1' && arr[i + 1][j] != 'x')
		game->map.is_valid = 0; 
	
	if (i && arr[i - 1][j] == '0')
		flood_fill(arr, i - 1, j, game);
	else if (i && arr[i - 1][j] != '1' && arr[i - 1][j] != 'x')
		game->map.is_valid = 0;
	
	if (arr[i][j + 1] && arr[i][j + 1] == '0')
		flood_fill(arr, i, j + 1, game);
	else if (arr[i][j + 1] && arr[i][j + 1] != '1' && arr[i][j + 1] != 'x')
		game->map.is_valid = 0;

	if (j && arr[i][j - 1] == '0')
		flood_fill(arr, i, j - 1, game);
	else if (j && arr[i][j - 1] != '1' && arr[i][j - 1] != 'x')
		game->map.is_valid = 0; 
}


int main(void)
{
	t_game game;
	game.map.is_valid = 1;
	char **arr = ft_split("111111\n100f11\n000000\nfrnjlfr", '\n');
	flood_fill(arr, 1, 3, &game);
	printf("%i\n", game.map.is_valid);
}
