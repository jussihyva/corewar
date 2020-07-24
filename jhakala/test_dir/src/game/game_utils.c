/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 18:31:16 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/24 21:07:11 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

//void	run_statement(t_carriage *c)
//{

int		**get_argument_type_codes(int type)
{
	int **types;
	int i;

	types = (int**)malloc(sizeof(int*) * 3);
	i = 0;
	while (i < 3)
		types[i++] = (int*)malloc(sizeof(int*) * 2);
    types[0][0] = type >> 6;
    types[1][0] = (type >> 4) & 3;
    types[2][0] = (type >> 2) & 3;
	return (types);
}

int		possible_arg(int **types, int op_code)
{
	int i;
	int l;

	l = -1;
	while (++l < g_op_tab[op_code].n_arg)
	{
		i = g_op_tab[op_code].t_arg[l];
		if (types[l][0] == 1 && (i == 1 || i == 3 || i == 5 || i == 7))
			continue ;
		else if (types[l][0] == 2 && (i == 2 || i == 3 || i == 6 || i == 7))
			continue ;
		else if (types[l][0] == 3 && (i == 4 || i == 5 || i == 6 || i == 7))
			continue ;
		else
			return (1);
	}
	return (0);
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
	return (type);
}

int		arg_sizes(char *arena, int place, int **types, int code)
{
	int size;
	int i;

	size = 0;
	i = -1;
//	ft_printf("n_arg=%d\n", g_op_tab[(int)arena[place - 2] - 1].n_arg);
	while (++i < g_op_tab[(int)arena[place - 2] - 1].n_arg)
	{
		if (types[i][0] == 1)
		{
			types[i][1] = arena[place + size];
			size += 1;
//			ft_printf("-'%d'\n", types[i][1]);
		}
		else if (types[i][0] == 2)
		{
			types[i][1] = read_types(arena, place + size, g_op_tab[code - 1].s_dir);
			size += g_op_tab[code - 1].s_dir;
//			ft_printf("--'%d'\n", types[i][1]);
		}
		else if (types[i][0] == 3)
		{
			types[i][1] = read_types(arena, place + size, IND_SIZE);
			size += IND_SIZE;
//			ft_printf("---'%d'\n", types[i][1]);
		}
//		ft_printf("size=%d\n",size);
	}
	return (size);
}

int		read_game_param(char *arena, int from, int size, int **types)
{
	int i;

	i = 0;
	ft_printf("	(0x%04x -> 0x%04x) ", from, from + size > MEM_SIZE ?
			MEM_SIZE - (from + size) : from  + size);
	while (i < size)
	{
		if (from + i >= MEM_SIZE)
			from = -i;
		ft_printf("%02x ", (unsigned char)arena[from + i]);
		i++;
	}
	ft_printf("\n");
	if (types != NULL)
	{
		free(types[0]);
		free(types[1]);
		free(types[2]);
		free(types);
	}
	return (size);
}

int		read_statement_code(t_carriage *c, t_game *game, int place)
{
	if ((c->statement_code == game->arena[place] ||
		c->statement_code == -1) && game->arena[place] > 0 && game->arena[place] < 17)
		return (g_op_tab[game->arena[place] - 1].f(game, place, c));
	return (read_game_param(game->arena, place, 1, NULL));
}
