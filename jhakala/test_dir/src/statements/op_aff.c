/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:55:31 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/31 22:00:08 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_aff(t_game *game, int place, t_carriage *c)
{
	int **types;
	int size;

	types = get_argument_type_codes(game->arena[place + 1]);
	size = arg_sizes(game->arena, place + 2, types, game->arena[place]) + 2;
	if (possible_arg(types, game->arena[place] - 1))
		return (read_game_param(game->arena, place, size, types));
	ft_printf(" P   %d | aff r%d | %c", c->id, types[0][1], c->reg[types[0][1] - 1]);
	return (read_game_param(game->arena, place, size, types));
}
