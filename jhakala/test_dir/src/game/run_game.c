/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:41:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/08 14:47:14 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	cycle_through_c(t_game *game)
{
	t_carriage *c;

	c = game->c_lst;
//	ft_printf("cycle_n = '%d'\n", game->total_cycles);
	while (c)
	{
		if (c->remaining_cycle == 1)
			c->place = ft_place(ft_place(read_statement_code(c, game, c->place) + c->place));
		else if (c->remaining_cycle == 0)
		{
			c->statement_code = (game->arena[c->place] & 0xFF);
			if (c->statement_code > 0 && c->statement_code < 17)
				c->remaining_cycle = g_op_tab[c->statement_code - 1].n_cycles;
			else
			{
 				c->remaining_cycle = 1;
				c->place = ft_place(c->place + 1);
			}
		}
		c->remaining_cycle--;
		c = c->next;
	}
}		

void	print_player_weights(t_mem *mem)
{
	t_player *p;

	p = mem->player;
	while (p)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", p->id,
				REV(p->header->prog_size), p->header->prog_name, p->header->comment);
		p = p->next;
	}
}

int		run_game(t_mem *mem)
{
	t_game *game;

	print_player_weights(mem);
	game = mem->game;
	if (mem->dump == 0)
	{
		print_arena(game->arena);
		return (1);
	}
	while (game->c_lst)
	{
		cycle_through_c(game);
		if (--game->cycles_to_die <= 0)
		{
			if (check_carriages(game) == 1)
				break ;
		}
		if (game->total_cycles == mem->dump)
		{
			print_arena(game->arena);
			return (1);
		}
		game->total_cycles++;
	}
	return (0);
}
