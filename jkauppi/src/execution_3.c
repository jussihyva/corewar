/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 14:28:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 17:37:40 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_or(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	int			param[2];

	(void)asm_code;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] | param[1];
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_xor(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	int			param[2];

	(void)asm_code;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] ^ param[1];
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_and(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code)
{
	int			param[2];

	(void)asm_code;
	ft_bzero(param, sizeof(param));
	if (instruction->param[0].type == REG_CODE)
		param[0] = cpu->reg[instruction->param[0].value];
	if (instruction->param[2].type == REG_CODE)
		param[1] = cpu->reg[instruction->param[1].value];
	cpu->reg[instruction->param[2].value] = param[0] & param[1];
	cpu->pc = instruction->start_p + instruction->length;
	return ;
}
