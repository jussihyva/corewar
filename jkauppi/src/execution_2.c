/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:47:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/01 13:51:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_live(t_cpu *cpu, t_instruction *instruction)
{
	cpu->is_live += 1;
	cpu->pc = instruction->start_p + instruction->length;
	ft_printf("Live update %d(%d)\n", cpu->is_live, cpu->reg[1]);
	return ;
}

void			exec_fork(t_cpu *cpu, t_instruction *instruction)
{
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_sti(t_cpu *cpu, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	i = 0;
	if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else if (instruction->param[1].type == IND_CODE)
	{
		p = cpu->pc + instruction->param[1].value;
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
	}
	if (instruction->param[2].type == DIR_CODE)
		i += instruction->param[2].value;
	p = cpu->pc + i;
	p[0] = (cpu->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
	p[1] = (cpu->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
	p[2] = (cpu->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
	p[3] = (cpu->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_st(t_cpu *cpu, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	if (instruction->param[1].type == IND_CODE)
	{
		i = instruction->param[1].value;
		p = cpu->pc + i;
		p[0] = (cpu->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
		p[1] = (cpu->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
		p[2] = (cpu->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
		p[3] = (cpu->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
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
