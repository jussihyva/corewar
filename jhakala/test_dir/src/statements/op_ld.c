/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_ld.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:50:11 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/31 17:43:24 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_ld(t_game *game, int place, t_carriage *c)
{
	int **types;
	int size;

	types = get_argument_type_codes(game->arena[place + 1]);
	size = arg_sizes(game->arena, place + 2, types, game->arena[place]) + 2;
	if (possible_arg(types, game->arena[place] - 1))
		return (read_game_param(game->arena, place, size, types));
	ft_printf(" P   %d | ld", c->id);
	if (types[0][0] == 2)
		c->reg[types[1][1] - 1] = types[0][1];
	else
		c->reg[types[1][1] - 1] = read_types(game->arena, place + (types[0][1] % IDX_MOD), REG_SIZE);
	if (c->reg[types[1][1] - 1] == 0)
		c->carry = 1;
	else
		c->carry = 0;
	ft_printf(" %d r%d | %d | carry = %d\n", c->reg[types[1][1] - 1], types[1][1],
			c->reg[types[1][1] - 1], c->carry);
	return (read_game_param(game->arena, place, size, types));
}
