/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_lldi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:57 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/31 21:57:13 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_lldi(t_game *game, int place, t_carriage *c)
{
	int **types;
	int size;
	int val1;
	int val2;

	types = get_argument_type_codes(game->arena[place + 1]);
	size = arg_sizes(game->arena, place + 2, types, game->arena[place]) + 2;
	if (possible_arg(types, game->arena[place] - 1))
		return (read_game_param(game->arena, place, size, types));
	if (types[0][0] == 1)
		val1 = c->reg[types[0][1] - 1];
	else if (types[0][0] == 2)
		val1 = types[0][1];
	else
		val1 = read_types(game->arena, place + types[0][1], REG_SIZE);
	if (types[1][0] == 1)
		val2 = c->reg[types[1][1] - 1];
	else if (types[1][0] == 2)
		val2 = types[1][1];
	else
		val2 = read_types(game->arena, place + types[1][1], REG_SIZE);
	c->reg[types[2][1] - 1] = read_types(game->arena, place + (val1 + val2), REG_SIZE);
	ft_printf(" P   %d | lldi %d %d r%d\n", c->id, val1, val2, types[2][1]);
	return (read_game_param(game->arena, place, size, types));
}
