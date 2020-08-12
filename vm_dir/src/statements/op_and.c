/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_and.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:52:25 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 21:30:12 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_and_val(int i, int **types, t_game *game, t_carriage *c)
{
	int val;

	if (types[i][0] == 1)
		val = c->reg[types[i][1] - 1];
	else if (types[i][0] == 2)
		val = types[i][1];
	else
		val = read_types(game->arena, c->place + (types[i][1] % IDX_MOD),
						REG_SIZE);
	return (val);
}

int		op_and(t_game *game, int place, t_carriage *c)
{
	int **types;
	int val1;
	int val2;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	val1 = op_and_val(0, types, game, c);
	val2 = op_and_val(1, types, game, c);
	c->reg[types[2][1] - 1] = val1 & val2;
	if (c->reg[types[2][1] - 1] == 0)
		c->carry = 1;
	else
		c->carry = 0;
	if (game->print)
		ft_printf(" P   %d | and %d %d r%d | carry = %d\n", c->id, val1, val2,
				types[2][1], c->carry);
	return (read_game_param(game, place, c->size, types));
}
