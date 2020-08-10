/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_add.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:51:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 21:33:39 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_add(t_game *game, int place, t_carriage *c)
{
	int **types;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (game->print)
		ft_printf(" P   %d | add r%d r%d r%d", c->id, types[0][1], types[1][1],
			types[2][1]);
	if ((c->reg[types[2][1] - 1] = c->reg[types[0][1] - 1] +
		c->reg[types[1][1] - 1]) == 0)
		c->carry = 1;
	else
		c->carry = 0;
	if (game->print)
		ft_printf(" | add [%d] [%d] = [%d] | carry = %d\n",
				c->reg[types[0][1] - 1], c->reg[types[1][1] - 1],
				c->reg[types[2][1] - 1], c->carry);
	return (read_game_param(game, place, c->size, types));
}
