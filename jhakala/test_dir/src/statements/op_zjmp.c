/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:53:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/08 16:58:36 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_zjmp(t_game *game, int place, t_carriage *c)
{
	short res;
	short val1;

	res = 0 + ((unsigned char)game->arena[ft_place(place + 1)] << 8) +
		(unsigned char)game->arena[ft_place(place + 2)];
	if (c->carry == 1)
	{
		val1 = (res % IDX_MOD) - 3;
		if (val1 + c->place >= MEM_SIZE)
			c->place += val1 - MEM_SIZE;
		else if (val1 + c->place < 0)
			c->place += val1 + MEM_SIZE;
		else
			c->place += val1;
		if (game->print)
			ft_printf(" P   %d | zjmp %d | (0x%04x) | OK\n", c->id, res, ft_place(c->place));
	}
	else
	{
		if (game->print)
			ft_printf(" P   %d | zjmp %d | ERROR\n", c->id, res);
	}
	return (read_game_param(game->arena, place, 3, NULL));
}
