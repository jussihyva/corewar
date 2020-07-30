/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 11:02:28 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/30 15:07:47 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

t_process		*initialize_process(t_cpu *cpu, char *pc)
{
	t_process		*process;
	t_opcode		next_opcode;

	process = (t_process *)ft_memalloc(sizeof(*process));
	process->process_id = cpu->process_cnt;
	process->pc_index = pc - cpu->memory;
	process->program_start_ptr = cpu->memory + process->pc_index;
	process->reg[1] = -process->process_id;
	next_opcode = *(cpu->memory + process->pc_index);
	if (next_opcode > 0 && next_opcode < 17)
		process->cycle_point_for_next_instruction = cpu->cycle_cnt +
					cpu->g_op_tab[next_opcode].cycles;
	else
		process->cycle_point_for_next_instruction = cpu->cycle_cnt + 1;
	return (process);
}
