/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:52:07 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 20:54:09 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_sub(t_game *game, int place, t_carriage *c)
{
	int **types;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (game->print)
		ft_printf(" P   %d | sub r%d r%d r%d", c->id, types[0][1], types[1][1], types[2][1]);
	if ((c->reg[types[2][1] - 1] = c->reg[types[0][1] - 1] - c->reg[types[1][1] - 1]) == 0)
		c->carry = 1;
	else
		c->carry = 0;
	if (game->print)
		ft_printf(" | sub [%d] [%d] = [%d]", c->reg[types[0][1] - 1], c->reg[types[1][1] - 1],
				c->reg[types[2][1] - 1]);
	if (game->print)
		ft_printf(" | carry = %d\n", c->carry);
	return (read_game_param(game, place, c->size, types));
}
