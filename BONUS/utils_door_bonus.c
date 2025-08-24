/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_door_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:40 by abel-had          #+#    #+#             */
/*   Updated: 2025/08/24 13:25:04 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	remove_door(t_door **head, int x, int y)
{
	t_door	*current;
	t_door	*prev;

	if (!head || *head == NULL)
		return ;
	if ((*head)->x == x && (*head)->y == y)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
		return ;
	}
	prev = *head;
	current = (*head)->next;
	while (current != NULL)
	{
		if (current->x == x && current->y == y)
		{
			prev->next = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

static int	check_door_position(int player_x, int player_y, int j, int i)
{
	return ((player_x == j && player_y == i - 1)
		|| (player_x == j + 1 && player_y == i - 1)
		|| (player_x == j + 1 && player_y == i)
		|| (player_x == j + 1 && player_y == i + 1)
		|| (player_x == j && player_y == i + 1)
		|| (player_x == j - 1 && player_y == i + 1)
		|| (player_x == j - 1 && player_y == i)
		|| (player_x == j - 1 && player_y == i - 1));
}

int	zone_door(t_game *game, int i, int j)
{
	int	player_x;
	int	player_y;

	player_x = (int)game->player.x;
	player_y = (int)game->player.y;
	return (game->map.grid[i][j] == '2'
		&& check_door_position(player_x, player_y, j, i));
}

void	return_door(t_game *game, int i, int j)
{
	t_door	*current;
	int		player_x;
	int		player_y;

	current = game->closed_door;
	player_x = (int)game->player.x;
	player_y = (int)game->player.y;
	while (current)
	{
		if (current->x == j && current->y == i)
		{
			if (abs(player_x - j) > 1 || abs(player_y - i) > 1)
			{
				game->map.grid[i][j] = '2';
				remove_door(&game->closed_door, j, i);
				break ;
			}
		}
		current = current->next;
	}
}

void	open_the_door(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map_h)
	{
		j = 0;
		while (j < game->map_w)
		{
			if (zone_door(game, i, j))
			{
				game->map.grid[i][j] = '0';
				add_door_to_end(&game->closed_door, j, i);
			}
			else if (game->map.grid[i][j] == '0')
				return_door(game, i, j);
			j++;
		}
		i++;
	}
}
