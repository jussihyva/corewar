/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_live.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:47:41 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/23 17:52:37 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_live(t_game *game, int place, t_carriage *c)
{
	int res;

	ft_memcpy(&res, &game->arena[place + 1], 4);
	res = REV(res);
	ft_printf("	P   %d | live %d\n", c->id, res);
	if (res < 0 && res >= -(game->n_player))
	{
		game->last_alive = game->players[res];
		ft_printf("	called alive for player %d\n", -res);
	}
	return (read_game_param(game->arena, place, 5, NULL));
}