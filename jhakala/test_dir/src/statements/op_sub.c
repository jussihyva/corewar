/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:52:07 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/31 17:46:42 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_sub(t_game *game, int place, t_carriage *c)
{
	int **types;
	int size;

	types = get_argument_type_codes(game->arena[place + 1]);
	size = arg_sizes(game->arena, place + 2, types, game->arena[place]) + 2;
	if (possible_arg(types, game->arena[place] - 1))
		return (read_game_param(game->arena, place, size, types));
	ft_printf(" P   %d | sub r%d r%d r%d", c->id, types[0][1], types[1][1], types[2][1]);
	if ((c->reg[types[2][1] - 1] = c->reg[types[0][1] - 1] - c->reg[types[1][1] - 1]) == 0)
		c->carry = 1;
	else
		c->carry = 0;
	ft_printf(" | sub [%d] [%d] = [%d]", c->reg[types[0][1] - 1], c->reg[types[1][1] - 1],
			c->reg[types[2][1] - 1]);
	ft_printf(" | carry = %d\n", c->carry);
	return (read_game_param(game->arena, place, size, types));
}
