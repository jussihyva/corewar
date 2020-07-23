/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:02:28 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/23 11:46:44 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*initialize_process(t_cpu *cpu, char *pc)
{
	t_process		*process;

	process = (t_process *)ft_memalloc(sizeof(*process));
	process->process_id = cpu->process_cnt;
	process->pc = pc;
	process->program_start_ptr = process->pc;
	process->reg[1] = -process->process_id;
	process->next_instruction = parse_instruction(cpu, process->pc);
	process->cycle_point_for_next_instruction = cpu->cycle_cnt +
						cpu->g_op_tab[process->next_instruction->opcode].cycles;
	return (process);
}
