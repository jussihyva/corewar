/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:57 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/12 18:13:18 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_lldi(t_game *game, int place, t_carriage *c)
{
	int **types;
	int val1;
	int val2;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (types[0][0] == 1)
		val1 = c->reg[types[0][1] - 1];
	else if (types[0][0] == 2)
		val1 = (short)types[0][1];
	else
		val1 = read_types(game->arena, place + (short)types[0][1], REG_SIZE);
	if (types[1][0] == 1)
		val2 = c->reg[types[1][1] - 1];
	else if (types[1][0] == 2)
		val2 = (short)types[1][1];
	else
		val2 = read_types(game->arena, place + (short)types[1][1], REG_SIZE);
	c->reg[types[2][1] - 1] = read_types(game->arena, place + (val1 + val2),
										REG_SIZE);
	if (game->print)
		ft_printf(" P   %d | lldi %d %d r%d\n",
					c->id, val1, val2, types[2][1]);
	return (read_game_param(game, place, c->size, types));
}
