/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lfork.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:55:15 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/08 16:54:44 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_lfork(t_game *game, int place, t_carriage *c)
{
	int val;

	val = game->arena[ft_place(place + 2)] & 0xFF;
	val += (game->arena[ft_place(place + 1)] << 8);
	new_carriage(&game->c_lst, place, c, game);
	game->c_lst->place = ft_place(game->c_lst->place + val);
	if (game->print)
		ft_printf(" P   %d | lfork %d | to (0x%04x)\n", c->id, val, game->c_lst->place);
	return (read_game_param(game->arena, place, 3, NULL));
}
