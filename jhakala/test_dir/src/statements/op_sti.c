/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_sti.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:54:08 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/24 21:43:56 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int    op_sti(t_game *game, int place, t_carriage *c)
{
    int **types;
    int size;
	int val1;
	int val2;

    types = get_argument_type_codes(game->arena[place + 1]);
    size = arg_sizes(game->arena, place + 2, types, game->arena[place]) + 2;
    if (possible_arg(types, game->arena[place] - 1))
        return (read_game_param(game->arena, place, size, types));
	val1 = types[1][0] == 1 ? c->reg[types[1][1] - 1] : types[1][1];
	val2 = types[2][0] == 1 ? c->reg[types[2][1] - 1] : types[2][1];
	ft_printf(" P   %d | sti r%d %d %d\n", c->id, types[0][0], val1, val2);
	game->arena[place + val1 + val2] = (c->reg[types[0][1] - 1] >> 24) & 0xFF;
	game->arena[place + val1 + val2 + 1] = (c->reg[types[0][1] - 1] >> 16) & 0xFF;
	game->arena[place + val1 + val2 + 2] = (c->reg[types[0][1] - 1] >> 8) & 0xFF;
	game->arena[place + val1 + val2 + 3] = c->reg[types[0][1] - 1] & 0xFF;
//	ft_printf("", game, place, c);
//	ft_printf("sti \n");
	return (read_game_param(game->arena, place, size, types));
}
