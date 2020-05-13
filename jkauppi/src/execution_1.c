/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/13 15:58:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_live(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->is_live = 1;
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_ld(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	(void)asm_code;
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

void			exec_ldi(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	size_t		i;
	char		*p;

	(void)asm_code;
	if (instruction->param[0].type == DIR_CODE && instruction->param[1].type == DIR_CODE)
	{
		i = 0;
		i += instruction->param[0].value;
		i += instruction->param[1].value;
		p = cpu->PC + i;
		cpu->reg[instruction->param[2].value] = 0;
		cpu->reg[instruction->param[2].value] += p[0] << (8 * 2);
		cpu->reg[instruction->param[2].value] += p[1] << (8 * 1);
		cpu->reg[instruction->param[2].value] += p[2] << (8 * 0);
		ft_printf("%08p: %p\n", p - asm_code->file_content, cpu->PC - asm_code->file_content);
	}
	else
	{
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_zjmp(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	(void)asm_code;
	if (instruction->param[0].type == DIR_CODE)
		cpu->PC += instruction->param[0].value;
	else
	{
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		cpu->PC += instruction->param[0].value;
	}
	return ;
}

void			exec_sti(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	size_t		i;
	char		*p;

	(void)asm_code;
	if (instruction->param[1].type == DIR_CODE && instruction->param[2].type == DIR_CODE)
	{
		i = 0;
		i += instruction->param[1].value;
		i += instruction->param[2].value;
		p = cpu->PC + i;
		p[0] = (cpu->reg[instruction->param[0].value] >> (8 * 2)) * 0xff;
		p[1] = (cpu->reg[instruction->param[0].value] >> (8 * 1)) * 0xff;
		p[2] = (cpu->reg[instruction->param[0].value] >> (8 * 0)) * 0xff;
//		ft_printf("%08p: %p\n", p - asm_code->file_content, cpu->PC - asm_code->file_content);
	}
	else
	{
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}