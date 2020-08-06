/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:53:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/06 17:37:07 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		op_zjmp(t_game *game, int place, t_carriage *c)
{
	short res;
	short val1;

	res = 0;
	ft_memcpy(&res, &game->arena[ft_place(place + 1)], 2);
//	res = 0 + (game->arena[ft_place(place + 2)] << 8);
//	res += (game->arena[ft_place(place + 1)]);
//	ft_printf("res=%x,\n", res); //(shoREV_S(res));
	res = REV_S(res);
	if (c->carry == 1)
	{
		val1 = (res % IDX_MOD) - 3;
		if (val1 + c->place >= MEM_SIZE)
			c->place += val1 - MEM_SIZE;
		else if (val1 + c->place < 0)
			c->place += val1 + MEM_SIZE;
		else
			c->place += val1;
		ft_printf(" P   %d | zjmp %d | (0x%04x) | OK\n", c->id, res, ft_place(c->place));
	}
	else
		ft_printf(" P   %d | zjmp %d | ERROR\n", c->id, res);
	return (read_game_param(game->arena, place, 3, NULL));
}
