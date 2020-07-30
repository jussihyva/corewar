/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/30 14:51:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_ld(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	(void)cpu;
	if (instruction->param[0].type == DIR_CODE)
	{
		process->reg[instruction->param[1].value] = instruction->param[0].value;
		process->carry = (instruction->param[0].value) ? 0 : 1;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_index);
		print_hex_string(0, cpu->memory + instruction->start_index, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}

static int		save_pointer_value_to_reg(char *p)
{
	int			value;

	value = 0;
	value += p[1] << (8 * 3);
	value += p[2] << (8 * 2);
	value += p[3] << (8 * 1);
	value += p[4] << (8 * 0);
	ft_printf("%x\n", p);
	ft_printf("%d\n", p[0]);
	ft_printf("%d\n", p[1]);
	ft_printf("%d\n", p[2]);
	ft_printf("%d\n", p[3]);
	ft_printf("%d\n", p[4]);
	return (value);
}

void			exec_ldi(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	(void)cpu;
	i = 0;
	if (instruction->param[0].type == DIR_CODE)
		i += instruction->param[0].value;
	else if (instruction->param[0].type == IND_CODE)
	{
		p = cpu->memory + ((process->pc_index + instruction->param[0].value) % MEM_SIZE);
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
	}
	else
		ft_printf("%08x: ", instruction->start_index);
	if (instruction->param[1].type == REG_CODE)
		i += process->reg[instruction->param[1].value];
	else if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else
		ft_printf("%08p:", instruction->start_index);
	p = cpu->memory + ((process->pc_index + i) % MEM_SIZE);
	process->reg[instruction->param[2].value] = save_pointer_value_to_reg(p);
	process->pc_index = (instruction->start_index + instruction->length) % MEM_SIZE;
}

void			exec_sub(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	(void)cpu;
	process->reg[instruction->param[2].value] =
									process->reg[instruction->param[0].value] -
									process->reg[instruction->param[1].value];
	process->carry = (process->reg[instruction->param[2].value]) ? 0 : 1;
	process->pc_index = (instruction->start_index + instruction->length) % MEM_SIZE;
	return ;
}

void			exec_add(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	(void)cpu;
	process->reg[instruction->param[2].value] =
									process->reg[instruction->param[0].value] +
									process->reg[instruction->param[1].value];
	process->carry = (process->reg[instruction->param[2].value]) ? 0 : 1;
	process->pc_index = (instruction->start_index + instruction->length) % MEM_SIZE;
	return ;
}
