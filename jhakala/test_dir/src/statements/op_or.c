/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_or.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:52:44 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 20:54:23 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_or(t_game *game, int place, t_carriage *c)
{
	int **types;
	int val1;
	int val2;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (types[0][0] == 1)
		val1 = c->reg[types[0][1] - 1];
	else if (types[0][0] == 2)
		val1 = types[0][1];
	else
		val1 = read_types(game->arena, place + (types[0][1] % IDX_MOD), REG_SIZE);
	if (types[1][0] == 1)
		val2 = c->reg[types[1][1] - 1];
	else if (types[1][0] == 2)
		val2 = types[1][1];
	else
		val2 = read_types(game->arena, place + (types[1][1] % IDX_MOD), REG_SIZE);
	c->reg[types[2][1] - 1] = val1 | val2;
	if (c->reg[types[2][1] - 1] == 0)
		c->carry = 1;
	else
		c->carry = 0;
	if (game->print)
		ft_printf(" P   %d | or %d %d r%d | carry = %d\n", c->id, val1, val2, types[2][1], c->carry);
	return (read_game_param(game, place, c->size, types));
}
