/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:47:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/23 13:46:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_live(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	(void)cpu;
	process->is_live += 1;
	process->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_fork(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	t_process		*new_process;
	char			*new_pc;
	t_list			*process_elem;
	int				i;

	cpu->process_cnt++;
	new_pc = process->pc + instruction->param[0].value;
	new_process = initialize_process(cpu, new_pc);
	i = -1;
	while (++i < REG_NUMBER)
		new_process->reg[i] = process->reg[i];
	new_process->carry = process->carry;
	new_process->is_live = process->is_live;
	new_process->is_killed = process->is_killed;
	process_elem = ft_lstnew(&new_process, sizeof(new_process));
	ft_lstadd(&cpu->process_list, process_elem);
	process->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_sti(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	(void)cpu;
	i = 0;
	if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else if (instruction->param[1].type == IND_CODE)
	{
		p = process->pc + instruction->param[1].value;
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
	}
	if (instruction->param[2].type == DIR_CODE)
		i += instruction->param[2].value;
	p = process->pc + i;
	p[0] = (process->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
	p[1] = (process->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
	p[2] = (process->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
	p[3] = (process->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
	process->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_st(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	(void)cpu;
	if (instruction->param[1].type == IND_CODE)
	{
		i = instruction->param[1].value;
		p = process->pc + i;
		p[0] = (process->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
		p[1] = (process->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
		p[2] = (process->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
		p[3] = (process->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - process->program_start_ptr +
															sizeof(t_header));
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	process->pc = instruction->start_p + instruction->length;
	return ;
}
