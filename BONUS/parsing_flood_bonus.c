/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_flood.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:03:56 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/24 12:43:59 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	push_to_queue(t_queue **head, int x, int y, t_game *game)
{
	t_queue	*new;

	if (x < 0 || y < 0 || game->arr[y] == NULL || game->arr[y][x] == 0 || \
	game->arr[y][x] == 'x' || game->arr[y][x] == '1')
		return ;
	new = malloc(sizeof(t_queue));
	if (!new)
	{
		clean_parsing_stuff(game);
		ft_putstr_fd("Error\allocation failed \n", 2);
		exit(EXIT_FAILURE);
	}
	new->x = x;
	new->y = y;
	new->next = *head;
	*head = new;
}

void	pop_from_queue(t_queue **head)
{
	t_queue	*tmp;

	tmp = *head;
	*head = (*head)->next;
	free(tmp);
}

void	clean_queue(t_queue **head)
{
	t_queue	*tmp;

	while (*head)
	{
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
	}
}

int	process_neighbors(t_queue **head, int x, int y, t_game *game)
{
	if (x < 0 || y < 0 || game->arr[y] == NULL || game->arr[y][x] == 0 || \
		game->arr[y][x] == 'x' || game->arr[y][x] == '1')
		return (1);
	else if (game->arr[y][x] != 'v')
		return (0);
	else
	{
		game->arr[y][x] = 'x';
		push_to_queue(head, x + 1, y + 1, game);
		push_to_queue(head, x + 1, y, game);
		push_to_queue(head, x, y + 1, game);
		push_to_queue(head, x - 1, y - 1, game);
		push_to_queue(head, x - 1, y + 1, game);
		push_to_queue(head, x + 1, y - 1, game);
		push_to_queue(head, x - 1, y, game);
		push_to_queue(head, x, y - 1, game);
	}
	return (1);
}

int	iter_flood_check(char **arr, int x, int y, t_game *game)
{
	t_queue	*head;

	head = malloc(sizeof(t_queue));
	if (!head)
	{
		clean_parsing_stuff(game);
		ft_putstr_fd("Error\allocation failed \n", 2);
		exit(EXIT_FAILURE);
	}
	game->arr = arr;
	head->x = x;
	head->y = y;
	head->next = NULL;
	while (head)
	{
		x = head->x;
		y = head->y;
		pop_from_queue(&head);
		if (!process_neighbors(&head, x, y, game))
			return (clean_queue(&head), 0);
	}
	return (1);
}
