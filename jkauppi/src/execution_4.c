/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:01:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/22 15:59:21 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_zjmp(t_process *process, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
	{
		if (process->carry)
			process->pc += instruction->param[0].value;
		else
			process->pc = instruction->start_p + instruction->length;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - process->program_start_ptr +
															sizeof(t_header));
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		process->pc += instruction->param[0].value;
	}
	return ;
}
