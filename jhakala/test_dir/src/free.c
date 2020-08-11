/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:11:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 14:22:10 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#include <stdio.h>

int		free_int(int *arr)
{
	free(arr);
	return (1);
}

int		free_game(t_mem *mem)
{
	t_carriage *c;
	t_carriage *tmp;

	c = mem->game->c_lst;
	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}
	c = mem->game->vara;
	while (c)
	{
		tmp = c;
		c = c->next;
		free(tmp);
	}
	if (mem->game->arena)
		free(mem->game->arena);
	free(mem->game->players);
//	free(mem->game);
	return (1);
}

int		free_memory(t_mem *mem)
{
	t_player *p;
	t_player *tmp;

	p = mem->player;
	while (p)
	{
		if (p->header)
			free(p->header);
		if (p->input)
			free(p->input);
		tmp = p;
		p = p->next;
		free(tmp);
	}
	if (mem->game)
	{
		ft_printf("here\n");
		free_game(mem);
	}
//	free(mem);
	return (1);
}
