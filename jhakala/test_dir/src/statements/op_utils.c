/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 12:19:55 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 21:08:14 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		ft_place(int place)
{
	if (place >= MEM_SIZE)
		return (place - MEM_SIZE);
	else if (place < 0)
		return (place + MEM_SIZE);
	return (place);
}

int		**get_argument_type_codes(int type)
{
	int **types;
	int i;

	types = (int**)malloc(sizeof(int*) * 3);
	i = 0;
	while (i < 3)
		types[i++] = (int*)malloc(sizeof(int*) * 2);
	types[0][0] = (type >> 6) & 3;
	types[1][0] = (type >> 4) & 3;
	types[2][0] = (type >> 2) & 3;
	return (types);
}

int		arg_sizes(char *arena, int place, int **types, int code)
{
	int size;
	int i;

	size = 0;
	i = -1;
	while (++i < g_op_tab[code].n_arg)
	{
		if (types[i][0] == 1)
		{
			types[i][1] = arena[ft_place(place + size)];
			size += 1;
		}
		else if (types[i][0] == 2)
		{
			types[i][1] = read_types(arena, place + size, g_op_tab[code].s_dir);
			size += g_op_tab[code].s_dir;
		}
		else if (types[i][0] == 3)
		{
			types[i][1] = read_types(arena, place + size, IND_SIZE);
			size += IND_SIZE;
		}
	}
	return (size);
}

int		read_game_param(t_game *game, int from, int size, int **types)
{
	char	*arena;
	int		i;

	if (game->print)
	{
		i = 0;
		arena = game->arena;
		ft_printf("	(0x%04x -> 0x%04x) ", from, from + size >= MEM_SIZE ?
				MEM_SIZE - (from + size) : from + size);
		while (i < size)
		{
			ft_printf("%02x ", (unsigned char)arena[ft_place(from + i)]);
			i++;
		}
		ft_printf("\n");
	}
	if (types != NULL)
	{
		free(types[0]);
		free(types[1]);
		free(types[2]);
		free(types);
	}
	return (size);
}

int		**get_arg_types(t_game *game, t_carriage *c)
{
	int **types;

	types = get_argument_type_codes(game->arena[ft_place(c->place + 1)]);
	c->size = arg_sizes(game->arena, c->place + 2, types,
					c->statement_code - 1) + 2;
	if (possible_arg(types, game->arena[c->place] - 1))
	{
		ft_printf("%d failed: ", c->id);
		read_game_param(game, c->place, c->size, types);
		return (NULL);
	}
	return (types);
}
