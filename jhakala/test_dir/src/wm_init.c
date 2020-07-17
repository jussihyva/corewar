/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wm_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 17:30:36 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/17 19:35:31 by jhakala          ###   ########.fr       */
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
	ft_printf("\n");
	ft_printf("\n");
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
		p = p->next;
	}
}

void	wm_default_values(t_game *game, t_mem *mem)
{
	game->c_lst = NULL;
	game->last_alive = mem->n_player;
	game->total_cycles = 0;
	game->n_live_in_cycle = 0;
	game->cycles_to_die = CYCLE_TO_DIE;
}

t_game	*wm_init(t_mem *mem)
{
	t_game *game;

	game = (t_game*)malloc(sizeof(t_game));
	game->arena = (char*)malloc(sizeof(char) * MEM_SIZE);
	ft_bzero(game->arena, MEM_SIZE);
	print_arena(game->arena);
	put_player_input_to_arena(game, mem);
	print_arena(game->arena);
	return (game);
}
