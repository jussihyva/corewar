/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:30:36 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/23 17:54:46 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_arena(char *arena)
{
	int i;

	i = 0;
	system("clear");
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0)
			ft_printf("\n");
		ft_printf("%02x ", (unsigned char)arena[i++]);
	}
	ft_printf("\n\n");
}

void	put_player_input_to_arena(t_game *game, t_mem *mem)
{
	t_player *p;
	int i;
	int place;

	p = mem->player;
	i = 0;
	while (p)
	{
		place = MEM_SIZE / mem->n_player * i++;
		ft_memcpy(&game->arena[place], p->input, REV(p->header->prog_size));
		new_carriage(&game->c_lst, place, NULL, p->id);
		p = p->next;
	}
}

void	wm_default_values(t_game *game, t_mem *mem)
{
	t_player *p;
	int i;

	p = mem->player;
	game->players = (t_player**)malloc(sizeof(t_player*) * mem->n_player);
//need to free him at the end
	i = 0;
	while (p->next)
	{
		game->players[i++] = p;
		p = p->next;
	}
	game->c_lst = NULL;
	game->last_alive = p;
	game->total_cycles = 1;
	game->n_live_in_cycle = 0;
	game->cycles_to_die = CYCLE_TO_DIE;
	game->n_player = mem->n_player;
}

t_game	*wm_init(t_mem *mem)
{
	t_game *game;

	game = (t_game*)malloc(sizeof(t_game));
	game->arena = (char*)malloc(sizeof(char) * MEM_SIZE);
	wm_default_values(game, mem);
	ft_bzero(game->arena, MEM_SIZE);
//	print_arena(game->arena);
	put_player_input_to_arena(game, mem);
	print_arena(game->arena);
	return (game);
}
