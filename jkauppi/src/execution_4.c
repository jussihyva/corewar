/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:01:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/01 14:02:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_zjmp(t_cpu *cpu, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
	{
		if (cpu->carry)
			cpu->pc += instruction->param[0].value;
		else
			cpu->pc = instruction->start_p + instruction->length;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - cpu->program_start_ptr +
															sizeof(t_header));
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		cpu->pc += instruction->param[0].value;
	}
	return ;
}
