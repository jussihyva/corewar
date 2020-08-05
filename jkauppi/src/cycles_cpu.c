/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_cpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/08/05 19:26:59 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			verbose_print(t_cpu *cpu, t_process *process,
										int *is_cycle_printed, int carry_old)
{
	t_opcode		opcode;
	char			*result_string;
	unsigned char	*ptr;
	unsigned char	*end_ptr;

	opcode = process->next_instruction->opcode;
	if (cpu->opt & verbose || cpu->opt & verbose1)
	{
		if (cpu->opt & verbose ||
			cpu->g_op_tab[process->next_instruction->opcode].opcode == e_live)
		{
			ft_printf("Cycle : %lld (%4lld) ", cpu->cycle_cnt,
									cpu->cycle_to_die_point - cpu->cycle_cnt);
			*is_cycle_printed = 1;
			result_string = ft_strnew(sizeof(*result_string) * 100);
			if (cpu->check_carry & 1 << opcode)
				ft_sprintf(result_string, "    (carry=%d)", process->carry);
			else if (cpu->modify_carry & 1 << opcode)
				ft_sprintf(result_string, "    (carry: %d-->%d)", carry_old, process->carry);
			else
				ft_sprintf(result_string, " ");
			ft_printf("P %5d | %s ", process->process_id,
			cpu->g_op_tab[process->next_instruction->opcode].instruction_name);
			print_params(process->next_instruction->param);
			ft_printf("%30s", result_string);
			ft_strdel(&result_string);
		}
		end_ptr = cpu->memory + process->next_instruction->start_index + process->next_instruction->length;
		ptr = cpu->memory + process->next_instruction->start_index;
		ft_printf("    %08x: ", process->next_instruction->start_index);
		while (ptr < end_ptr)
		{
			ft_printf(" %.2x", (unsigned char)*ptr);
			ptr++;
		}
		ft_printf("\n");
	}
	return ;
}

static int			are_players_alive(t_list *process_list)
{
	t_process		*process;
	int				num_of_players_alive;
	size_t			i;
	t_list			*process_elem;

	num_of_players_alive = 0;
	i = -1;
	process_elem = process_list;
	while (process_elem)
	{
		process = *(t_process **)process_elem->content;
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
		process_elem = process_elem->next;
	}
	return (num_of_players_alive);
}

long long			set_cycle_to_die_point(t_cpu *cpu)
{
	long long		cycle_to_die_point;

	cycle_to_die_point = cpu->cycle_cnt + cpu->current_cycle_to_die;
	ft_printf("%160s %d\n", "Updated cycle to die cnt:",
													cpu->current_cycle_to_die);
	return (cycle_to_die_point);
}

static int			execute_instruction(t_cpu *cpu, t_process *process,
														int *is_cycle_printed)
{
	int			carry_old;
	t_opcode	opcode;
	int			player;

	player = 0;
	carry_old = process->carry;
	opcode = *(cpu->memory + process->pc_index);
	if (opcode > 0 && opcode < 17)
	{
		process->next_instruction = parse_instruction(cpu, cpu->memory + process->pc_index);
		cpu->op_function[process->next_instruction->opcode](cpu, process,
											process->next_instruction);
		verbose_print(cpu, process, is_cycle_printed, carry_old);
		if (cpu->g_op_tab[process->next_instruction->opcode].opcode ==
																	e_live)
		{
			cpu->total_num_of_live_instructions++;
			ft_printf("%148s%d\n", "Sum of live: ",
									cpu->total_num_of_live_instructions);
			player = -process->next_instruction->param[0].value;
		}
		free(process->next_instruction);
		process->next_instruction = NULL;
	}
	else
	{
		ft_printf("P %5d | %.2x <-- Unknown opcode!\n", process->process_id,
												(unsigned char)opcode);
		process->pc_index = (process->pc_index + 1) % MEM_SIZE;
	}
	opcode = *(cpu->memory + process->pc_index);
	if (opcode > 0 && opcode < 17)
		process->cycle_point_for_next_instruction = cpu->cycle_cnt +
						cpu->g_op_tab[opcode].cycles;
	else
		process->cycle_point_for_next_instruction = cpu->cycle_cnt + 1;
	return (player);
}

int					execute_cycle(t_cpu *cpu, t_list *process_list,
														t_input *input)
{
	int				num_of_players_alive;
	t_process		*process;
	int				is_cycle_printed;
	t_list			*process_elem;
	int				player;

	is_cycle_printed = 0;
	num_of_players_alive = 0;
	cpu->cycle_cnt++;
	process_elem = process_list;
	while (process_elem)
	{
		process = *(t_process **)process_elem->content;
		if (!process->is_killed &&
					process->cycle_point_for_next_instruction == cpu->cycle_cnt)
		{
			player = execute_instruction(cpu, process, &is_cycle_printed);
			if (player > 0 && player <= input->num_of_players)
				input->players[player - 1]->last_live_cycle = cpu->cycle_cnt;
		}
		process_elem = process_elem->next;
	}
	if (cpu->cycle_cnt == cpu->cycle_to_die_point)
	{
		num_of_players_alive = are_players_alive(process_list);
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
				process_elem = process_list;
				while (process_elem)
				{
					process = *(t_process **)process_elem->content;
					if (!process->is_killed)
					{
						process->is_killed = 1;
						ft_printf("Process %d hasn't lived for xx cycles (CTD %d)\n", process->process_id, cpu->current_cycle_to_die);
					}
					process_elem = process_elem->next;
				}
			}
			cpu->current_number_of_checks = 0;
		}
		cpu->total_num_of_live_instructions = 0;
		if (cpu->current_cycle_to_die > 0)
			cpu->cycle_to_die_point = set_cycle_to_die_point(cpu);
	}
	else
		num_of_players_alive = input->num_of_players;
	return (num_of_players_alive);
}
