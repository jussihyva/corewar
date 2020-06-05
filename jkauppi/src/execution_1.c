/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 12:02:21 by ubuntu           ###   ########.fr       */
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
		ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
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
		if (asm_code->g_op_tab[e_ldi].label_size)
		{
			cpu->reg[instruction->param[2].value] += p[0] << (8 * 1);
			cpu->reg[instruction->param[2].value] += p[1] << (8 * 0);
		}
		else
			ft_printf("%08p: %p\n", p - asm_code->file_content, cpu->PC - asm_code->file_content);
		// ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
		// ft_printf("reg%d: %d", instruction->param[2].value, cpu->reg[instruction->param[2].value]);
		// ft_printf(" (pointer: %08p)", p - cpu->program_start_ptr + sizeof(*asm_code->header));
		// ft_printf("\n");
	}
	else if (instruction->param[0].type == DIR_CODE && instruction->param[1].type == REG_CODE)
	{
		i = 0;
		i += instruction->param[0].value;
		i += cpu->reg[instruction->param[1].value];
		p = cpu->PC + i;
		cpu->reg[instruction->param[2].value] = 0;
		if (asm_code->g_op_tab[e_ldi].label_size)
		{
			cpu->reg[instruction->param[2].value] += p[0] << (8 * 1);
			cpu->reg[instruction->param[2].value] += p[1] << (8 * 0);
		}
		else
			ft_printf("%08p: %p\n", p - asm_code->file_content, cpu->PC - asm_code->file_content);
		// ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
		// ft_printf("reg%d: %d", instruction->param[2].value, cpu->reg[instruction->param[2].value]);
		// ft_printf(" (pointer: %08p)", p - cpu->program_start_ptr + sizeof(*asm_code->header));
		// ft_printf("\n");
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
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
		ft_printf("%08x: ", instruction->start_p - asm_code->file_content);
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		cpu->PC += instruction->param[0].value;
	}
	return ;
}

void			exec_sub(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->reg[instruction->param[2].value] =
										cpu->reg[instruction->param[0].value] -
										cpu->reg[instruction->param[1].value];
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_add(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	(void)asm_code;
	cpu->reg[instruction->param[2].value] =
										cpu->reg[instruction->param[0].value] +
										cpu->reg[instruction->param[1].value];
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_or(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	int			param[2];

	(void)asm_code;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] | param[1];
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}

void			exec_and(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code)
{
	int			param[2];

	(void)asm_code;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] & param[1];
	cpu->PC = instruction->start_p + instruction->length;
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
	cpu->PC = instruction->start_p + instruction->length;
	return ;
}