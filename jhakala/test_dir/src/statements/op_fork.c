/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:24 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/31 22:01:15 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_fork(t_game *game, int place, t_carriage *c)
{
	int val;

	val = game->arena[place + 2] & 0xFF;
	val += (game->arena[place + 1] << 8);
	new_carriage(&game->c_lst, place, c, game);
	game->c_lst->place += (val % IDX_MOD);
	ft_printf(" P   %d | fork %d | to (0x%04x)\n", c->id, val, game->c_lst->place);
	return (read_game_param(game->arena, place, 3, NULL));
}
