/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:31:16 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/22 23:14:41 by jhakala          ###   ########.fr       */
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

int read_types(char *arena, int from, int size)
{
	int type;
	int times;

	type = 0;
	times = 0;
	while (--size > -1)
	{
		type += arena[from + size] << (8 * times);
		times++;
	}
	ft_printf("--------type='%x'\n", type);
	return (type);
}

int		arg_sizes(char *arena, int place, int types[3][2], int code)
{
	int size;
	int i;

	size = 0;
	i = -1;
	while (++i < 3)
	{

		if (types[i][0] == 1)
		{
			size += 1;
//			types[i] = 0;
			types[i][1] = arena[place];
			ft_printf("-'%d'\n", types[i][1]);
		}
		else if (types[i][0] == 2)
		{
			types[i][1] = read_types(arena, place + size, g_op_tab[code - 1].s_dir);
			size += g_op_tab[code - 1].s_dir;
//			types[i] = 0;
			ft_printf("--'%d'\n", types[i][1]);
		}
		else if (types[i][0] == 3)
		{
			types[i][1] = read_types(arena, place + size, IND_SIZE);
			size += IND_SIZE;
//			types[i] = 0;
			ft_printf("---'%d'\n", types[i][1]);
		}
	}
	return (size);
}

int		read_statement_code(t_carriage *c, t_game *game, int place)
{
	int types[3][2];
	int type;
	int i;
	int size;

	size = 1; //statement_code
	ft_printf("arena.place->'%d''%02x'\n", game->arena[place], game->arena[place]);
	if ((c->statement_code == game->arena[place] || c->statement_code == -1) && game->arena[place] > 0 && game->arena[place] < 17)
	{
		size += 1; //argument_type_code
		if (g_op_tab[game->arena[place] - 1].type == 1)
		{
			type = game->arena[place + 1];
			types[0][0] = type >> 6;
			types[1][0] = (type >> 4) & 3;
			types[2][0] = (type >> 2) & 3;
			ft_printf("type = '%x'\n", type);
			ft_printf("AAAAAAAAAA0=%d, 1=%d, 2=%d\n", types[0][0], types[1][0], types[2][0]);
			size += arg_sizes(game->arena, place + 2, types, game->arena[place]); //arguments sizes
//			ft_printf("SIZE='%d'\n", size);
			i = 0;
			while (i < 3)
			{
				if (possible_arg(types[i][0], game->arena[place] - 1, i) != 0)
				{
					ft_printf("invalid type/arg\n");
					return (size);
				}
				i++;
			}
			ft_printf("0=%d, 1=%d, 2=%d\n", types[0][0], types[1][0], types[2][0]);
			//run statement_code who has argument_type_codes
			if (game->arena[place] == 3)
			{
				ft_printf("heeargfadgag\n");
				st(game, place, types, c);
				
			}
			
			
		}
		else
		{
//			run different;
			
		}
	}
	else
		return (1);
	return (0);
}
