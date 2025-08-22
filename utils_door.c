#include "cub.h"

void add_door_to_end(t_door **head, int x, int y)
{
	t_door *new_door;
	t_door *current;
	
	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return;
	new_door->x = x;
	new_door->y = y;
	new_door->next = NULL;
	if (*head == NULL)
	{
		*head = new_door;
		return;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_door;
}

void remove_door(t_door **head, int x, int y)
{
	t_door *current;
	t_door *prev;
	 if (!head || *head == NULL)
		return;
	if ((*head)->x == x && (*head)->y == y)
	{
		current = *head;
		*head = (*head)->next;
		free(current);
		return;
	}
	prev = *head;
	current = (*head)->next;
	
	while (current != NULL)
	{
		if (current->x == x && current->y == y)
		{
			prev->next = current->next;
			free(current);
			return;
		}
		prev = current;
		current = current->next;
	}
}

int zone_door(t_game *game, int i, int j)
{
	return (game->map.grid[i][j] == '2' && 
				(((int)game->player.x == j && (int)game->player.y == i - 1) || 
				 ((int)game->player.x == j + 1 && (int)game->player.y == i - 1) ||
				 ((int)game->player.x == j + 1 && (int)game->player.y == i) ||
				 ((int)game->player.x == j + 1 && (int)game->player.y == i + 1) ||
				 ((int)game->player.x == j && (int)game->player.y == i + 1) ||
				 ((int)game->player.x == j - 1 && (int)game->player.y == i + 1) ||
				 ((int)game->player.x == j - 1 && (int)game->player.y == i) ||
				 ((int)game->player.x == j - 1 && (int)game->player.y == i - 1)));
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
				break;
			}
		}
		current = current->next;
	}
}
void	open_the_door(t_game *game)
{
	int i;
	int j;

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

void free_all_doors(t_door **head)
{
	t_door *current;
	t_door *next;
	
	if (!head)
		return;
		
	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}