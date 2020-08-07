/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:08 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/07 20:07:07 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_sti(t_game *game, t_carriage *c, int **types, short value)
{
	ft_printf(" P   %d | sti r%d", c->id, types[0][1]);
	if ( types[1][0] == 1)
		ft_printf(" %d", c->reg[types[1][1] - 1]);
	else if (types[1][0] == 2)
		ft_printf(" %d", (short)types[1][1]);
	else
		ft_printf(" %d", read_types(game->arena, c->place + types[1][1] % IDX_MOD, 4));
	if (types[2][0] == 1)
		ft_printf(" %d", c->reg[types[2][1] - 1]);
	else
		ft_printf(" %d", (short)types[2][1]);
	ft_printf(" | %d %% IDX_MOD", value);
}

int		op_sti(t_game *game, int place, t_carriage *c)
{
	int **types;
	int val1;
	short val2;

	val1 = 0;
	val2 = 0;
	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (types[1][0] == 1)
		val1 = c->reg[types[1][1] - 1];
	else if (types[1][0] == 2)
		val2 = types[1][1];
	else
		val1 = read_types(game->arena, place + types[1][1] % IDX_MOD, 4);
	val1 += val2 + (types[2][0] == 1 ? c->reg[types[2][1] - 1] : types[2][1]);
	print_sti(game, c, types, val1);
	val1 = val1 % IDX_MOD;
	ft_printf(" | (0x%04x -> 0x%04x)\n", ft_place(place + val1), ft_place(place + val1 + 3));
	game->arena[ft_place(place + val1)] = (c->reg[types[0][1] - 1] >> 24) & 0xFF;
	game->arena[ft_place(place + val1 + 1)] = (c->reg[types[0][1] - 1] >> 16) & 0xFF;
	game->arena[ft_place(place + val1 + 2)] = (c->reg[types[0][1] - 1] >> 8) & 0xFF;
	game->arena[ft_place(place + val1 + 3)] = c->reg[types[0][1] - 1] & 0xFF;
	return (read_game_param(game->arena, place, c->size, types));
}
