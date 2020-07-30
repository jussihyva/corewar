/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:28:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/30 14:57:36 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_or(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	int			param[2];

	(void)cpu;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = process->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = process->reg[instruction->param[1].value];
	process->reg[instruction->param[2].value] = param[0] | param[1];
	process->carry = (process->reg[instruction->param[2].value]) ? 0 : 1;
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}

void			exec_xor(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	int			param[2];

	(void)cpu;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = process->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = process->reg[instruction->param[1].value];
	process->reg[instruction->param[2].value] = param[0] ^ param[1];
	process->carry = (process->reg[instruction->param[2].value]) ? 0 : 1;
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}

void			exec_and(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	int			param[2];

	(void)cpu;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = process->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = process->reg[instruction->param[1].value];
	process->reg[instruction->param[2].value] = param[0] & param[1];
	process->carry = (process->reg[instruction->param[2].value]) ? 0 : 1;
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}
