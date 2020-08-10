/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:55:31 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 21:20:07 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_aff(t_game *game, int place, t_carriage *c)
{
	int **types;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (game->print)
		ft_printf(" P   %d | aff r%d | %c", c->id, types[0][1],
				c->reg[types[0][1] - 1]);
	return (read_game_param(game, place, c->size, types));
}
