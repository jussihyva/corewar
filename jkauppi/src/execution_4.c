/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:01:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/30 15:00:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_zjmp(t_cpu *cpu, t_process *process,
													t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
	{
		if (process->carry)
			process->pc_index += instruction->param[0].value;
		else
			process->pc_index = instruction->start_index + instruction->length;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_index);
		print_hex_string(0, cpu->memory + instruction->start_index,
														instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		process->pc_index += instruction->param[0].value;
	}
	return ;
}
