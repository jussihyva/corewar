/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/13 14:07:07 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_live(t_cpu *cpu, t_instruction *instruction)
{
	cpu->is_live = 1;
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_ld(t_cpu *cpu, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
		cpu->reg[instruction->param[1].value] = instruction->param[0].value;
	else
	{
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_zjmp(t_cpu *cpu, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
		cpu->PC = instruction->start_p + instruction->length;
	else
	{
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	return ;
}
