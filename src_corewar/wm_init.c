/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:30:36 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/16 16:44:15 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_arena(char *arena, t_mem *mem)
{
/*	int i;

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
*/
	int i;
	int row;
	int cap;

	i = 0;
	row = 0;
	cap = 1;
	mvprintw(0, 0, "0x%04x : ", i);
	attron(COLOR_PAIR (mem->game->owner[i]));
	mvprintw(0, 9, "%02x ", (unsigned char)arena[i++]);
	mem->dump_type = 64;
	while (i < MEM_SIZE)
	{
		attroff(COLOR_PAIR (mem->game->owner[i - 1]));
		if (i % mem->dump_type == 0)
		{
			row++;
			mvprintw(row, 0,  "0x%04x : ", i);
			cap = 0;
		}
		attron(COLOR_PAIR (mem->game->owner[i]));
		mvprintw(row, 9 + cap * 3, "%02x ", (unsigned char)arena[i++]);
		cap++;
	}
	attroff(COLOR_PAIR (mem->game->owner[i - 1]));
	refresh();
//	ft_printf("\n");
}

void	put_player_input_to_arena(t_game *game, t_mem *mem)
{
	t_player	*p;
	int			i;
	int			place;
	unsigned int count;

	p = mem->player;
	i = 0;
	while (p)
	{
		count = 0;
		place = MEM_SIZE / mem->n_player * i++;
		ft_memcpy(&game->arena[place], p->input, REV(p->header->prog_size));
		new_carriage(&game->c_lst, place, NULL, game);
		while (count < REV(p->header->prog_size))
			game->owner[place + count++] = game->c_lst->owner;
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
	game->owner = (int*)malloc(sizeof(int) * MEM_SIZE);
	ft_bzero(game->owner, MEM_SIZE);
	wm_default_values(game, mem);
	ft_bzero(game->arena, MEM_SIZE);
	put_player_input_to_arena(game, mem);
	return (game);
}
