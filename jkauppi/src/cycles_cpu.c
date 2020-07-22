/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_cpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/22 16:44:40 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int			are_players_alive(t_process **process_list, size_t num_of_players)
{
	t_process		*process;
	int				num_of_players_alive;
	size_t			i;

	num_of_players_alive = 0;
	i = -1;
	while (++i < num_of_players)
	{
		process = process_list[i];
		if (!process->is_killed)
		{
			if (process->is_live)
				num_of_players_alive++;
			else
			{
				process->is_killed = 1;
				ft_printf("Player %d is killed\n", i + 1);
			}
			process->is_live = 0;
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

static void			execute_instruction(t_cpu *cpu, t_process *process,
														int *is_cycle_printed)
{
	if (cpu->opt & verbose || cpu->opt & verbose1)
	{
		if (cpu->opt & verbose ||
			cpu->g_op_tab[process->next_instruction->opcode].opcode == e_live)
		{
			if (!*is_cycle_printed)
			{
				ft_printf("Cycle : %lld (%lld)\n", cpu->cycle_cnt,
									cpu->cycle_to_die_point - cpu->cycle_cnt);
				*is_cycle_printed = 1;
			}
			ft_printf("Execute instruction %u(%s) for player %u\n",
				process->next_instruction->opcode,
				cpu->g_op_tab[process->next_instruction->opcode].
											instruction_name, process->process_id);
		}
	}
	cpu->op_function[process->next_instruction->opcode](process,
										process->next_instruction);
	if (cpu->g_op_tab[process->next_instruction->opcode].opcode ==
																e_live)
	{
		cpu->total_num_of_live_instructions++;
		ft_printf("Total num of live instructions: %d\n",
								cpu->total_num_of_live_instructions);
	}
	free(process->next_instruction);
	process->next_instruction = parse_instruction(cpu, process->pc);
	process->cycle_point_for_next_instruction = cpu->cycle_cnt +
				cpu->g_op_tab[process->next_instruction->opcode].cycles;
	return ;
}

int					execute_cycle(t_cpu *cpu, t_process **process_list,
														size_t num_of_players)
{
	int				num_of_players_alive;
	t_process		*process;
	size_t			i;
	int				is_cycle_printed;

	is_cycle_printed = 0;
	num_of_players_alive = 0;
	cpu->cycle_cnt++;
	i = -1;
	while (++i < num_of_players)
	{
		process = process_list[i];
		if (!process->is_killed &&
					process->cycle_point_for_next_instruction == cpu->cycle_cnt)
			execute_instruction(cpu, process, &is_cycle_printed);
	}
	if (cpu->cycle_cnt == cpu->cycle_to_die_point)
	{
		num_of_players_alive = are_players_alive(process_list, num_of_players);
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
					process = process_list[i];
					if (!process->is_killed)
					{
						process->is_killed = 1;
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
