/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/01 12:45:03 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_ld(t_cpu *cpu, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
	{
		cpu->reg[instruction->param[1].value] = instruction->param[0].value;
		cpu->carry = (instruction->param[0].value) ? 0 : 1;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - cpu->program_start_ptr +
															sizeof(t_header));
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_ldi(t_cpu *cpu, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	i = 0;
	if (instruction->param[0].type == DIR_CODE)
		i += instruction->param[0].value;
	else if (instruction->param[0].type == IND_CODE)
	{
		p = cpu->pc + instruction->param[0].value;
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
		// i += p[3] << (8 * 1);
		// i += p[4] << (8 * 0);
		// ft_printf("%d\n", p[0]);
		// ft_printf("%d\n", p[1]);
		// ft_printf("%d\n", p[2]);
		// ft_printf("%d\n", p[3]);
		// ft_printf("%d\n", p[4]);
	}
	else
		ft_printf("%08x: ", instruction->start_p - cpu->program_start_ptr +
															sizeof(t_header));
	if (instruction->param[1].type == REG_CODE)
		i += cpu->reg[instruction->param[1].value];
	else if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else
		ft_printf("%08p: %p", cpu->program_start_ptr + sizeof(t_header),
			instruction->start_p - cpu->program_start_ptr + sizeof(t_header));
	p = cpu->pc + i;
	cpu->reg[instruction->param[2].value] = 0;
	cpu->reg[instruction->param[2].value] += p[1] << (8 * 3);
	cpu->reg[instruction->param[2].value] += p[2] << (8 * 2);
	cpu->reg[instruction->param[2].value] += p[3] << (8 * 1);
	cpu->reg[instruction->param[2].value] += p[4] << (8 * 0);
	cpu->pc = instruction->start_p + instruction->length;
	ft_printf("%x\n", p);
	ft_printf("%d\n", p[0]);
	ft_printf("%d\n", p[1]);
	ft_printf("%d\n", p[2]);
	ft_printf("%d\n", p[3]);
	ft_printf("%d\n", p[4]);
	return ;
}

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

void			exec_sub(t_cpu *cpu, t_instruction *instruction)
{
	cpu->reg[instruction->param[2].value] =
										cpu->reg[instruction->param[0].value] -
										cpu->reg[instruction->param[1].value];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_add(t_cpu *cpu, t_instruction *instruction)
{
	cpu->reg[instruction->param[2].value] =
										cpu->reg[instruction->param[0].value] +
										cpu->reg[instruction->param[1].value];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}
