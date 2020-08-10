/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/24 13:00:59 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 20:36:04 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	kill_head_carriage(t_carriage **alst, t_carriage *c, t_game *game)
{
	*alst = c->next;
	if (game->print)
		ft_printf("	KILL P   %d\n", c->id);
	free(c);
}

void	kill_carriage(t_carriage *prev, t_carriage *c, t_game *game)
{
	prev->next = c->next;
	if (game->print)
		ft_printf("	KILL P   %d\n", c->id);
	free(c);
}

void	check_kills(t_game *game)
{
	t_carriage *c;
	t_carriage *prev;

	c = game->c_lst;
	if (game->print)
		ft_printf("	MAKE CHECK\n");
	while (c && c->live_cycle == -1)
	{
		kill_head_carriage(&game->c_lst, c, game);
		c = game->c_lst;
	}
	while (c)
	{
		if (c->live_cycle == -1)
			kill_carriage(prev, c, game);
		else
			prev = c;
		prev->live_cycle = -1;
		c = prev->next;
	}
}

int		check_carriages(t_game *game)
{
	check_kills(game);
	if (game->c_lst == NULL)
		return (1);
	if (game->n_live_in_cycle >= NBR_LIVE)
	{
		game->get_die -= CYCLE_DELTA;
		game->max_check = 0;
	}
	else
	{
		if (++game->max_check >= MAX_CHECKS)
		{
			game->get_die -= CYCLE_DELTA;
			game->max_check = 0;
		}
	}
	if (game->print)
		ft_printf("	nbr_live=%d, get_die=%d\n", game->n_live_in_cycle,
				game->get_die);
	game->n_live_in_cycle = 0;
	game->cycles_to_die = game->get_die > 0 ? game->get_die : 1;
	return (0);
}
