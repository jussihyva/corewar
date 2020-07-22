/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 21:25:37 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/22 23:19:53 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	st(t_game *game, int place, int types[3][2], t_carriage *c)
{
	if (types[1][0] == 1 && types[1][1] > 0 && types[1][1] < 17)
		c->reg[types[1][1] - 1] = c->reg[types[0][1] - 1];
	else if (types[1][0] == 3)
	{
		ft_printf("VIaaaaaaaaaaaaaaaaaTTU, %d, %d, %d, %d\n", place, types[0][1], types[1][1], place + types[1][1]);
		ft_printf("c->re='%d'\n", c->reg[types[0][1] - 1]);
		game->arena[place + types[1][1]] = (c->reg[types[0][1] - 1] >> 24) & 0xFF;
		game->arena[place + types[1][1] + 1] = (c->reg[types[0][1] - 1] >> 16) & 0xFF;
		game->arena[place + types[1][1] + 2] = (c->reg[types[0][1] - 1] >> 8) & 0xFF;
		game->arena[place + types[1][1] + 3] = c->reg[types[0][1] - 1] & 0xFF;
	}
//	ft_printf
	ft_printf("VITTU\n");
}
		
