/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:41:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/22 22:11:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		cycle_through_c(t_game *game)
{
	t_carriage *c;
	int	size;

	c = game->c_lst;
	while (c)
	{
		if (c->remaining_cycle == 1)
		{
			size = read_statement_code(c, game, c->place);
			c->place = c->place + size;
			ft_printf("id'%d'place='%d'\n", c->id, c->place);
			//check if statement_code is good to go with arguments that are ahead
		}
		else if (c->remaining_cycle == 0)
		{
			ft_printf("id='%d'place='%d'\n", c->id, c->place);
			c->statement_code = game->arena[c->place];
			ft_printf("here\n");
			if (c->statement_code > 0 && c->statement_code < 17)
				c->remaining_cycle = g_op_tab[c->statement_code - 1].n_cycles;
			else
				c->remaining_cycle = 1;
		}
		c->remaining_cycle--;
		c = c->next;
	}
//jos fork niin mee kattomaan mita niil pitais teha?
	return (0);
}		

int		run_game(t_mem *mem)
{
	t_game *game;

	game = mem->game;
	while (game->c_lst)
	{
		cycle_through_c(game);
		if (game->total_cycles == mem->dump)
		{
			print_arena(game->arena);
			ft_printf("printf dump at '%d==%d' cycles\n", game->total_cycles, mem->dump);
			return (1);
		}
		game->total_cycles++;
	}
	return (0);
}
