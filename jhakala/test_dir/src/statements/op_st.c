/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:25:37 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/06 16:23:02 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_st(t_game *game, int place, t_carriage *c)
{
	int **types;

	if (!(types = get_arg_types(game, c)))
		return (c->size);
	ft_printf("	P   %d | st r%d ", c->id, types[0][1]);
	if (types[1][0] == 1 && types[1][1] > 0 && types[1][1] < 17)
	{
		c->reg[types[1][1] - 1] = c->reg[types[0][1] - 1];
		ft_printf("r%d\n", types[1][1]);
	}
	else if (types[1][0] == 3)
	{
		types[1][1] = types[1][1] % IDX_MOD;
		game->arena[ft_place(place + types[1][1])] = (c->reg[types[0][1] - 1] >> 24) & 0xFF;
		game->arena[ft_place(place + types[1][1] + 1)] = (c->reg[types[0][1] - 1] >> 16) & 0xFF;
		game->arena[ft_place(place + types[1][1] + 2)] = (c->reg[types[0][1] - 1] >> 8) & 0xFF;
		game->arena[ft_place(place + types[1][1] + 3)] = c->reg[types[0][1] - 1] & 0xFF;
		ft_printf("%d\n", types[1][1]);
	}
	return (read_game_param(game->arena, place, c->size, types));
}
