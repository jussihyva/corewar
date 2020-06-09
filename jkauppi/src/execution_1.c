/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/09 12:52:09 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_ld(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	(void)asm_code;
	if (instruction->param[0].type == DIR_CODE)
	{
		cpu->reg[instruction->param[1].value] = instruction->param[0].value;
		cpu->carry = (instruction->param[0].value) ? 0 : 1;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_ldi(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	size_t		i;
	char		*p;

	(void)asm_code;
	i = 0;
	if (instruction->param[0].type == DIR_CODE)
		i += instruction->param[0].value;
	else
		ft_printf("%08p: %p\n", asm_code->file_content,
											cpu->pc - asm_code->file_content);
	if (instruction->param[1].type == REG_CODE)
		i += cpu->reg[instruction->param[1].value];
	else if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else
		ft_printf("%08p: %p\n", asm_code->file_content,
											cpu->pc - asm_code->file_content);
	p = cpu->pc + i;
	cpu->reg[instruction->param[2].value] = 0;
	cpu->reg[instruction->param[2].value] += p[0] << (8 * 1);
	cpu->reg[instruction->param[2].value] += p[1] << (8 * 0);
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_zjmp(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	(void)asm_code;
	if (instruction->param[0].type == DIR_CODE)
	{
		if (cpu->carry)
			cpu->pc += instruction->param[0].value;
		else
			cpu->pc = instruction->start_p + instruction->length;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		cpu->pc += instruction->param[0].value;
	}
	return ;
}

void			exec_sub(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->reg[instruction->param[2].value] =
										cpu->reg[instruction->param[0].value] -
										cpu->reg[instruction->param[1].value];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_add(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->reg[instruction->param[2].value] =
										cpu->reg[instruction->param[0].value] +
										cpu->reg[instruction->param[1].value];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}
