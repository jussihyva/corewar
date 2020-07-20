/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:31:16 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/20 20:17:08 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

//void	run_statement(t_carriage *c)
//{


int		possible_arg(int type, int j, int k)
{
	int i;

	i = g_op_tab[j].t_arg[k];
	if (type == 1 && (i == 1 || i == 3 || i == 5 || i == 7))
		return (0);
	else if (type == 2 && (i == 2 || i == 3 || i == 6 || i == 7))
		return (0);
	else if (type == 3 && (i == 4 || i == 5 || i == 6 || i == 7))
		return (0);
	else if (type == 0)
		return (0);
	return (1);
}

int		read_statement_code(t_carriage *c, char *arena, int place)
{
	int types[3];
	int type;
	int i;
	
	ft_printf("arena.place->'%d''%02x'\n", arena[place], arena[place]);
	if ((c->statement_code == arena[place] || c->statement_code == -1) && arena[place] > 0 && arena[place] < 17)
	{
		if (g_op_tab[arena[place] - 1].type == 1)
		{
			type = arena[place + 1];
			types[0] = type >> 6;
			types[1] = -(type << 26 >> 30);
			types[2] =  -(type << 28 >> 30);
			i = 0;
			while (i < 3)
			{
				if (possible_arg(types[i], arena[place] - 1, i) != 0)
				{
					ft_printf("invalid type/arg\n");
					return (1);
				}
				i++;
			}
			ft_printf("0=%d, 1=%d, 2=%d\n", types[0], types[1], types[2]);
		}
	}
	else
		return (1);
	return (0);
}
