/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils_0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbour <aelbour@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 10:04:28 by aelbour           #+#    #+#             */
/*   Updated: 2025/08/22 13:04:14 by aelbour          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	ft_strjoin_char(char **str, char c, size_t size, t_game *game)
{
	char	*to_add;
	char	*tmp;

	to_add = malloc(size + 1);
	if (!to_add)
		return (clean_parsing_stuff(game), exit(1));
	ft_memset(to_add, c, size);
	to_add[size] = 0;
	tmp = *str;
	*str = ft_strjoin(*str, to_add, game);
	free(tmp);
	free(to_add);
}

void	ft_fix_sizes(char **arr, char c, t_game *game)
{
	size_t	max;
	size_t	i;

	i = 0;
	max = ft_strlen(arr[i]);
	while (arr[++i])
		if (ft_strlen(arr[i]) > max)
			max = ft_strlen(arr[i]);
	i = -1;
	while (arr[++i])
	{
		if (ft_strlen(arr[i]) < max)
			ft_strjoin_char(&arr[i], c, max - ft_strlen(arr[i]), game);
	}
}

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

int	iter_flood_check(char **arr, int x, int y, t_game *game)
{
	t_queue	*head;

	(void)game;
	head = malloc(sizeof(t_queue));
	game->arr = arr;
	if (!head)
	{
		clean_parsing_stuff(game);
		ft_putstr_fd("Error\allocation failed \n", 2);
		exit(EXIT_FAILURE);
	}
	head->x = x;
	head->y = y;
	head->next = NULL;
	while (head)
	{
		x = head->x;
		y = head->y;
		pop_from_queue(&head);
		if (x < 0 || y < 0 || arr[y] == NULL || arr[y][x] == 0 || \
			arr[y][x] == 'x' || arr[y][x] == '1')
			continue ;
		else if (arr[y][x] != 'v')
			return (0);
		else
		{
			arr[y][x] = 'x';
			push_to_queue(&head, x + 1, y + 1, game);
			push_to_queue(&head, x + 1, y, game);
			push_to_queue(&head, x, y + 1, game);
			push_to_queue(&head, x - 1, y - 1, game);
			push_to_queue(&head, x - 1, y + 1, game);
			push_to_queue(&head, x + 1, y - 1, game);
			push_to_queue(&head, x - 1, y, game);
			push_to_queue(&head, x, y - 1, game);
		}
	}
	return (1);
}

int	surrended_walls_check(char **arr)
{
	int	j;
	int	i;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[i][++j])
		{
			if ((i == 0 || j == 0) && arr[i][j] != '1')
				return (0);
			else if ((!arr[i][j + 1] || !arr[i + 1]) && arr[i][j] != '1')
				return (0);
		}
	}
	return (1);
}

unsigned int	process_rgb_seq(char *line, int *i, \
							unsigned int *color, int *bytes)
{
	int	n;

	while (line[(*i)] == ' ')
		(*i)++;
	n = ft_atoi(line, i);
	if (n >= 0)
		(*color) = ((*color) << 8) | n;
	else
		return (0);
	while (line[(*i)] == ' ' && (*bytes))
		(*i)++;
	if (line[(*i)] != ',' && (*bytes))
		return (0);
	else if (line[(*i)] == ',' && (*bytes))
		(*i)++;
	return (1);
}

unsigned int	parse_color_rgb(char *line)
{
	int				i;
	unsigned int	color;
	int				bytes;

	i = 1;
	bytes = 3;
	color = 0;
	while (bytes)
	{
		bytes--;
		if (!process_rgb_seq(line, &i, &color, &bytes))
			return (-1);
	}
	while (line[i] == ' ')
		i++;
	if (line[i] != '\n')
		return (-1);
	return (color);
}
