/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_st.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:25:37 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 20:53:39 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	op_st_ind(int **types, t_game *game, int place, t_carriage *c)
{
	short	val;

	val = (short)types[1][1];
	val %= IDX_MOD;
	game->arena[ft_place(place + val)] = (c->reg[types[0][1] - 1] >> 24)
		& 0xFF;
	game->arena[ft_place(place + val + 1)] = (c->reg[types[0][1] - 1] >> 16)
		& 0xFF;
	game->arena[ft_place(place + val + 2)] = (c->reg[types[0][1] - 1] >> 8)
		& 0xFF;
	game->arena[ft_place(place + val + 3)] = c->reg[types[0][1] - 1] & 0xFF;
	if (game->print)
		ft_printf(" P   %d | st r%d %d %% IDX_MOD | (0x%04x -> 0x%04x)\n",
				c->id, types[0][1], (short)types[1][1], ft_place(place + val),
				ft_place(place + val + 3));
}

int		op_st(t_game *game, int place, t_carriage *c)
{
	int		**types;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	if (types[1][0] == 1 && types[1][1] > 0 && types[1][1] < 17)
	{
		c->reg[types[1][1] - 1] = c->reg[types[0][1] - 1];
		if (game->print)
			ft_printf(" P   %d | st r%d r%d\n", c->id, types[0][1],
					types[1][1]);
	}
	else if (types[1][0] == 3)
		op_st_ind(types, game, place, c);
	return (read_game_param(game, place, c->size, types));
}
