/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:47:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 17:53:07 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_live(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->is_live = 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_fork(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_sti(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	size_t		i;
	char		*p;

	(void)asm_code;
	if (instruction->param[1].type == DIR_CODE &&
										instruction->param[2].type == DIR_CODE)
	{
		i = 0;
		i += instruction->param[1].value;
		i += instruction->param[2].value;
		p = cpu->pc + i;
		p[0] = (cpu->reg[instruction->param[0].value] >> (8 * 3)) * 0xff;
		p[1] = (cpu->reg[instruction->param[0].value] >> (8 * 2)) * 0xff;
		p[2] = (cpu->reg[instruction->param[0].value] >> (8 * 1)) * 0xff;
		p[3] = (cpu->reg[instruction->param[0].value] >> (8 * 0)) * 0xff;
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

void			exec_st(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	size_t		i;
	char		*p;

	(void)asm_code;
	if (instruction->param[1].type == IND_CODE)
	{
		i = instruction->param[1].value;
		p = cpu->pc + i;
		p[0] = (cpu->reg[instruction->param[0].value] >> (8 * 3)) * 0xff;
		p[1] = (cpu->reg[instruction->param[0].value] >> (8 * 2)) * 0xff;
		p[2] = (cpu->reg[instruction->param[0].value] >> (8 * 1)) * 0xff;
		p[3] = (cpu->reg[instruction->param[0].value] >> (8 * 0)) * 0xff;
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
