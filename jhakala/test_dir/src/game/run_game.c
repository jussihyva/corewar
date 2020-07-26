/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:41:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/26 19:45:47 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		cycle_through_c(t_game *game)
{
	t_carriage *c;
	int	size;

	c = game->c_lst;
	ft_printf("cycle_n = '%d'\n", game->total_cycles);
	while (c)
	{
		if (c->place >= MEM_SIZE)
		{
//			ft_printf("c->place >= MEM_SIZE");
			c->place -= MEM_SIZE;
		}
		else if (c->place < 0)
		{
//			ft_printf("c->place < 0");
			c->place += MEM_SIZE;
		}
		if (c->remaining_cycle == 1)
		{
			size = read_statement_code(c, game, c->place);
			c->place = c->place + size;
//			ft_printf("id'%d'place='%d'\n", c->id, c->place);
		}
		else if (c->remaining_cycle == 0)
		{
//			ft_printf("id='%d'place='%d'\n", c->id, c->place);
			
			c->statement_code = (game->arena[c->place] & 0xFF);
			if (c->statement_code > 0 && c->statement_code < 17)
				c->remaining_cycle = g_op_tab[c->statement_code - 1].n_cycles;
			else
			{
//				ft_printf("	place%d->%02x, ", c->id, game->arena[c->place]);
//				ft_printf("	%d\n", c->place);
 				c->remaining_cycle = 1;
				c->place++;
			}
		}
		c->remaining_cycle--;
		c = c->next;
	}
//jos fork niin mee kattomaan mita niil pitais teha?
	return (0);
}		

void	print_player_weights(t_mem *mem)
{
	t_player *p;

	p = mem->player;
	while (p)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n", p->id, REV(p->header->prog_size),
				p->header->prog_name, p->header->comment);
		p = p->next;
	}
}

int		run_game(t_mem *mem)
{
	t_game *game;

	print_player_weights(mem);
	game = mem->game;
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
			ft_printf("printf dump at '%d==%d' cycles\n", game->total_cycles, mem->dump);
			return (1);
		}
		game->total_cycles++;
	}
	return (0);
}
