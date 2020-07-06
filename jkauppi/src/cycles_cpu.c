/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_cpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/06 18:33:33 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

static int			is_player_alive(t_player *player)
{
	int				is_alive;

	is_alive = 1;
	if (!player->is_live)
		is_alive = 0;
	player->is_live = 0;
	return (is_alive);
}

int					execute_cycle(t_cpu *cpu, t_player **players,
														size_t num_of_players)
{
	int				num_of_players_alive;
	size_t			i;

	num_of_players_alive = 0;
	cpu->cycle_cnt++;
	ft_printf("Cycle : %lld (%lld)\n", cpu->cycle_cnt,
								cpu->next_cycle_to_die_point - cpu->cycle_cnt);
	i = -1;
	while (++i < num_of_players)
	{
		if (!(--players[i]->cycles_to_execute))
		{
			cpu->op_function[players[i]->next_instruction->opcode](players[i],
												players[i]->next_instruction);
			free(players[i]->next_instruction);
			players[i]->next_instruction = parse_instruction(cpu,
														players[i]->pc);
		}
	}
	if (cpu->cycle_cnt == cpu->next_cycle_to_die_point)
	{
		i = -1;
		while (++i < num_of_players)
		{
			if (is_player_alive(players[i]))
				num_of_players_alive++;
			else
				ft_printf("Player %d is killed\n", i + 1);
		}
		cpu->current_number_of_checks++;
		if (players[0]->is_live >= NBR_LIVE ||
					cpu->current_number_of_checks >= MAX_CHECKS)
		{
			cpu->current_cycle_to_die -= CYCLE_DELTA;
			if (cpu->current_cycle_to_die < 0)
				num_of_players_alive = 0;
			cpu->current_number_of_checks = 0;
		}
		cpu->next_cycle_to_die_point = cpu->cycle_cnt +
											cpu->current_cycle_to_die;
		ft_printf("  Updated cycle to die cnt: %d\n",
											cpu->current_cycle_to_die);
	}
	else
		num_of_players_alive = num_of_players;
	return (num_of_players_alive);
}
