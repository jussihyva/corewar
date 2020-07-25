/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_zjmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:53:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/25 18:21:40 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int    op_zjmp(t_game *game, int place, t_carriage *c)
{
	int res;

	res = 0;
	ft_memcpy(&res, &game->arena[place + 1], 2);
	res = REV_S(res);
	if (c->carry == 1)
	{
		c->place += (res % IDX_MOD) - 3;
		ft_printf(" P   %d | zjmp %d | OK\n", c->id, res);
	}
	else
		ft_printf(" P   %d | zjmp %d | ERROR\n", c->id, res);
	return (read_game_param(game->arena, place, 3, NULL));
}
