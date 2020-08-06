/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lld.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:42 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/06 16:32:24 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_lld(t_game *game, int place, t_carriage *c)
{
	int **types;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (types[0][0] == 2)
		c->reg[types[1][1] - 1] = types[0][1];
	else
		c->reg[types[1][1] - 1] = read_types(game->arena, place + types[0][1], REG_SIZE);
	if (c->reg[types[1][1] - 1] == 0)
		c->carry = 1;
	else
		c->carry = 0;
	ft_printf(" P   %d | lld %d r%d | %d | carry = %d\n", c->id, c->reg[types[1][1] - 1], types[1][1],
			c->reg[types[1][1] - 1], c->carry);
	return (read_game_param(game->arena, place, c->size, types));
}
