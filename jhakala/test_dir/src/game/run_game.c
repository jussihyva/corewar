/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:41:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/20 20:18:54 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		cycle_through_c(t_game *game)
{
	t_carriage *c;

	c = game->c_lst;
	while (c)
	{
		if (c->remaining_cycle == 1)
		{
			if (!read_statement_code(c, game->arena, c->place))
			{
				exit(0);
//				run_statement;
			}
//			else
//				go_to_next_valid_statement;
			//check if statement_code is good to go with arguments that are ahead
			// do the code if possible
			// else go to next good code
		}
		if (c->remaining_cycle == 0)
		{
			// go to next statement_code
			// put c->remaining_cycle vastaamaan
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
			ft_printf("printf dump at '%d==%d' cycles\n", game->total_cycles, mem->dump);
			return (1);
		}
		game->total_cycles++;
	}
	return (0);
}
