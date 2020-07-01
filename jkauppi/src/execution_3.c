/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:28:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/01 12:41:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_or(t_cpu *cpu, t_instruction *instruction)
{
	int			param[2];

	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] | param[1];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_xor(t_cpu *cpu, t_instruction *instruction)
{
	int			param[2];

	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] ^ param[1];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_and(t_cpu *cpu, t_instruction *instruction)
{
	int			param[2];

	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] & param[1];
	cpu->carry = (cpu->reg[instruction->param[2].value]) ? 0 : 1;
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}
