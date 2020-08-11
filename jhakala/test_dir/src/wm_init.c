/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:30:36 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 21:40:08 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_arena(char *arena, t_mem *mem)
{
	int i;

	i = 0;
	ft_printf("0x%04x : ", i);
	ft_printf("%02x ", (unsigned char)arena[i++]);
	while (i < MEM_SIZE)
	{
		if (i % mem->dump_type == 0)
			ft_printf("\n0x%04x : ", i);
		ft_printf("%02x ", (unsigned char)arena[i++]);
	}
	ft_printf("\n");
}

void	put_player_input_to_arena(t_game *game, t_mem *mem)
{
	t_player	*p;
	int			i;
	int			place;

	p = mem->player;
	i = 0;
	while (p)
	{
		place = MEM_SIZE / mem->n_player * i++;
		ft_memcpy(&game->arena[place], p->input, REV(p->header->prog_size));
		new_carriage(&game->c_lst, place, NULL, game);
		p = p->next;
	}
}

void	get_player_to_arr(t_game *game, t_mem *mem)
{
	int			i;
	t_player	*p;

	i = 0;
	while (i < mem->n_player)
	{
		p = mem->player;
		while (p)
		{
			if (p->id == i + 1)
				break ;
			p = p->next;
		}
		if (p == NULL)
			exit(0);
		game->players[i] = p;
		game->last_alive = p;
		i++;
	}
}

void	wm_default_values(t_game *game, t_mem *mem)
{
	t_player	*p;
	int			i;

	p = mem->player;
	game->players = (t_player**)malloc(sizeof(t_player*) * mem->n_player);
	i = 0;
	get_player_to_arr(game, mem);
	game->print = mem->print;
	game->c_lst = NULL;
	game->total_cycles = 1;
	game->n_live_in_cycle = 0;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->n_player = mem->n_player;
	game->c_nbr = 1;
	game->get_die = CYCLE_TO_DIE;
	game->max_check = 0;
	game->tmp = NULL;
}

t_game	*wm_init(t_mem *mem)
{
	t_game *game;

	if (!(game = (t_game*)malloc(sizeof(t_game))))
		return (NULL);
	game->arena = (char*)malloc(sizeof(char) * MEM_SIZE);
	wm_default_values(game, mem);
	ft_bzero(game->arena, MEM_SIZE);
	put_player_input_to_arena(game, mem);
	return (game);
}
