/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:47:41 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 21:32:45 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_live(t_game *game, int place, t_carriage *c)
{
	int res;

	res = read_types(game->arena, place + 1, 4);
	c->live_cycle = game->total_cycles;
	game->n_live_in_cycle++;
	if (game->print)
		ft_printf(" P   %d | live %d", c->id, res);
	if (res < 0 && res >= -(game->n_player))
	{
		game->last_alive = game->players[(-res) - 1];
		if (game->print)
			ft_printf(" | called alive for player %d", -res);
	}
	if (game->print)
		ft_printf("\n");
	return (read_game_param(game, place, 5, NULL));
}
