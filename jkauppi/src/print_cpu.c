/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:46:25 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/22 15:53:54 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			print_cpu(t_cpu *cpu, t_input *input, t_process *process,
							t_instruction *instruction)
{
	int			reg;

	print_instruction(instruction, instruction->start_p - cpu->memory,
						input->g_op_tab[instruction->opcode].instruction_name);
	ft_printf("%85s", "CPU: ");
	reg = 0;
	while (++reg < 8)
		ft_printf(" r%d=%d", reg, process->reg[reg]);
	ft_printf(" is_live=%d", process->is_live);
	ft_printf(" carry=%d", process->carry);
	ft_printf(" cycles_to_die=%d", cpu->current_cycle_to_die);
	ft_printf("\n");
	return ;
}
