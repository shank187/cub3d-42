/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-had <abel-had@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 10:52:28 by abel-had          #+#    #+#             */
/*   Updated: 2025/08/25 10:21:00 by abel-had         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bonus.h"

void	free_all_doors(t_door **head)
{
	t_door	*current;
	t_door	*next;

	if (!head)
		return ;
	current = *head;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*head = NULL;
}

void	add_door_to_end(t_door **head, int x, int y)
{
	t_door	*new_door;
	t_door	*current;

	new_door = malloc(sizeof(t_door));
	if (!new_door)
		return ;
	new_door->x = x;
	new_door->y = y;
	new_door->next = NULL;
	if (*head == NULL)
	{
		*head = new_door;
		return ;
	}
	current = *head;
	while (current->next != NULL)
		current = current->next;
	current->next = new_door;
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*a;
	size_t			i;

	i = 0;
	a = (unsigned char *)b;
	while (i < len)
	{
		a[i] = (unsigned char)c;
		i++;
	}
	return (b);
}

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	error_exit(t_game *g, char *msg)
{
	int	i;

	i = -1;
	while (++i < 5)
		if (g->texs[i].img)
			mlx_destroy_image(g->mlx, g->texs[i].img);
	if (g->img.img)
		mlx_destroy_image(g->mlx, g->img.img);
	if (g->win)
		mlx_destroy_window(g->mlx, g->win);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit (1);
}
