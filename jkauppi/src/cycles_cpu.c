/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_cpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/07 13:56:19 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

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
	t_player		*player;
	size_t			i;
	int				is_cycle_printed;

	is_cycle_printed = 0;
	num_of_players_alive = 0;
	cpu->cycle_cnt++;
	i = -1;
	while (++i < num_of_players)
	{
		player = players[i];
		if (!player->is_killed &&
					player->cycle_point_for_next_instruction == cpu->cycle_cnt)
		{
			if (cpu->opt & verbose || cpu->opt & verbose1)
			{
				if (cpu->opt & verbose ||
					cpu->g_op_tab[player->next_instruction->opcode].opcode ==
																		e_live)
				{
					if (!is_cycle_printed)
					{
						ft_printf("Cycle : %lld (%lld)\n", cpu->cycle_cnt,
										cpu->next_cycle_to_die_point - cpu->cycle_cnt);
						is_cycle_printed = 1;
					}
					ft_printf("Execute instruction %u(%s) for player %u\n",
						player->next_instruction->opcode,
						cpu->g_op_tab[player->next_instruction->opcode].
													instruction_name, i + 1);
				}
			}
			cpu->op_function[player->next_instruction->opcode](player,
												player->next_instruction);
			if (cpu->g_op_tab[player->next_instruction->opcode].opcode ==
																		e_live)
			{
				cpu->total_num_of_live_instructions++;
				ft_printf("Total num of live instructions: %d\n", cpu->total_num_of_live_instructions);
			}
			free(player->next_instruction);
			player->next_instruction = parse_instruction(cpu, player->pc);
			player->cycle_point_for_next_instruction = cpu->cycle_cnt +
						cpu->g_op_tab[player->next_instruction->opcode].cycles;
		}
	}
	if (cpu->cycle_cnt == cpu->next_cycle_to_die_point)
	{
		i = -1;
		while (++i < num_of_players)
		{
			player = players[i];
			if (!player->is_killed)
			{
				if (is_player_alive(player))
					num_of_players_alive++;
				else
				{
					player->is_killed = 1;
					ft_printf("Player %d is killed\n", i + 1);
				}
			}
		}
		cpu->current_number_of_checks++;
		if (cpu->total_num_of_live_instructions >= NBR_LIVE ||
					cpu->current_number_of_checks >= MAX_CHECKS)
		{
			cpu->current_cycle_to_die -= CYCLE_DELTA;
			if (cpu->current_cycle_to_die < 0)
			{
				num_of_players_alive = 0;
				i = -1;
				while (++i < num_of_players)
				{
					player = players[i];
					if (!player->is_killed)
					{
						player->is_killed = 1;
						ft_printf("Player %d is killed\n", i + 1);
					}
				}
			}
			cpu->current_number_of_checks = 0;
		}
		cpu->total_num_of_live_instructions = 0;
		cpu->next_cycle_to_die_point = cpu->cycle_cnt +
											cpu->current_cycle_to_die;
		ft_printf("                            Updated cycle to die cnt: %d\n",
											cpu->current_cycle_to_die);
	}
	else
		num_of_players_alive = num_of_players;
	return (num_of_players_alive);
}
