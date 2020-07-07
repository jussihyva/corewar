/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_cpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/07 17:24:48 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			are_players_alive(t_player **players, size_t num_of_players)
{
	t_player		*player;
	int				num_of_players_alive;
	size_t			i;

	num_of_players_alive = 0;
	i = -1;
	while (++i < num_of_players)
	{
		player = players[i];
		if (!player->is_killed)
		{
			if (player->is_live)
				num_of_players_alive++;
			else
			{
				player->is_killed = 1;
				ft_printf("Player %d is killed\n", i + 1);
			}
			player->is_live = 0;
		}
	}
	return (num_of_players_alive);
}

long long			set_cycle_to_die_point(t_cpu *cpu)
{
	long long		cycle_to_die_point;

	cycle_to_die_point = cpu->cycle_cnt + cpu->current_cycle_to_die;
	ft_printf("%60s %d\n", "Updated cycle to die cnt:",
													cpu->current_cycle_to_die);
	return (cycle_to_die_point);
}

static void			execute_instruction(t_cpu *cpu, t_player *player,
														int *is_cycle_printed)
{
	if (cpu->opt & verbose || cpu->opt & verbose1)
	{
		if (cpu->opt & verbose ||
			cpu->g_op_tab[player->next_instruction->opcode].opcode == e_live)
		{
			if (!*is_cycle_printed)
			{
				ft_printf("Cycle : %lld (%lld)\n", cpu->cycle_cnt,
									cpu->cycle_to_die_point - cpu->cycle_cnt);
				*is_cycle_printed = 1;
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
		ft_printf("Total num of live instructions: %d\n",
								cpu->total_num_of_live_instructions);
	}
	free(player->next_instruction);
	player->next_instruction = parse_instruction(cpu, player->pc);
	player->cycle_point_for_next_instruction = cpu->cycle_cnt +
				cpu->g_op_tab[player->next_instruction->opcode].cycles;
	return ;
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
			execute_instruction(cpu, player, &is_cycle_printed);
	}
	if (cpu->cycle_cnt == cpu->cycle_to_die_point)
	{
		num_of_players_alive = are_players_alive(players, num_of_players);
		cpu->current_number_of_checks++;
		if (cpu->total_num_of_live_instructions >= NBR_LIVE ||
					cpu->current_number_of_checks >= MAX_CHECKS)
		{
			cpu->current_cycle_to_die -= CYCLE_DELTA;
			if (cpu->current_cycle_to_die < 0)
			{
				if (!is_cycle_printed)
				{
					ft_printf("Cycle : %lld (%lld)\n", cpu->cycle_cnt,
								cpu->cycle_to_die_point - cpu->cycle_cnt);
					is_cycle_printed = 1;
				}
				ft_printf("Number of cycles to die <= 0 (%d)\n",
													cpu->current_cycle_to_die);
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
		if (cpu->current_cycle_to_die > 0)
			cpu->cycle_to_die_point = set_cycle_to_die_point(cpu);
	}
	else
		num_of_players_alive = num_of_players;
	return (num_of_players_alive);
}
