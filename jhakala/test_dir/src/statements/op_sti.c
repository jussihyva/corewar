/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:08 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/06 17:16:00 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_sti(t_carriage *c, int **types, int value)
{
	ft_printf(" P   %d | sti r%d %d %d | %d %% IDX_MOD\n", c->id, types[0][0],
			  types[1][0] == 1 ? c->reg[types[1][1] - 1] : (short)types[1][1],
			  types[2][0] == 1 ? c->reg[types[2][1] - 1] : (short)types[2][1], value);
}

int		op_sti(t_game *game, int place, t_carriage *c)
{
	int **types;
	short val1;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (types[1][0] == 1)
		val1 = c->reg[types[1][1] - 1];
	else if (types[1][0] == 2)
		val1 = types[1][1];
	else
		val1 = read_types(game->arena, place, 2);
	val1 += types[2][0] == 1 ? c->reg[types[2][1] - 1] : types[2][1];
	print_sti(c, types, val1);
	val1 = val1 % IDX_MOD;
	game->arena[ft_place(place + val1)] = (c->reg[types[0][1] - 1] >> 24) & 0xFF;
	game->arena[ft_place(place + val1 + 1)] = (c->reg[types[0][1] - 1] >> 16) & 0xFF;
	game->arena[ft_place(place + val1 + 2)] = (c->reg[types[0][1] - 1] >> 8) & 0xFF;
	game->arena[ft_place(place + val1 + 3)] = c->reg[types[0][1] - 1] & 0xFF;
	return (read_game_param(game->arena, place, c->size, types));
}
