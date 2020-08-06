/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:47:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/05 19:55:39 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_live(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	(void)cpu;
	process->is_live += 1;
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}

void			exec_fork(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	t_process		*new_process;
	int				new_pc_index;
	t_list			*process_elem;
	int				i;

	cpu->process_cnt++;
	new_pc_index = (process->pc_index + (instruction->param[0].value % IDX_MOD)) % MEM_SIZE;
	new_process = initialize_process(cpu, new_pc_index);
	i = -1;
	while (++i < REG_NUMBER)
		new_process->reg[i] = process->reg[i];
	new_process->carry = process->carry;
	new_process->is_live = process->is_live;
	new_process->is_killed = process->is_killed;
	process_elem = ft_lstnew(&new_process, sizeof(new_process));
	ft_lstadd(&cpu->process_list, process_elem);
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}

void			exec_sti(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	size_t			i;
	unsigned char	*p;

	i = 0;
	if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else if (instruction->param[1].type == IND_CODE)
	{
		p = cpu->memory + process->pc_index + instruction->param[1].value;
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
	}
	if (instruction->param[2].type == DIR_CODE)
		i += instruction->param[2].value;
	else if (instruction->param[2].type == REG_CODE)
		i += process->reg[instruction->param[2].value];
	if (process->pc_index + i < 0)
		p = cpu->memory + (MEM_SIZE + ((process->pc_index + i) % MEM_SIZE));
	else
		p = cpu->memory + ((process->pc_index + i) % MEM_SIZE);
	p[0] = (process->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
	p[1] = (process->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
	p[2] = (process->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
	p[3] = (process->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
	process->pc_index = instruction->start_index + instruction->length;
	return ;
}

void			exec_st(t_cpu *cpu, t_process *process, t_instruction *instruction)
{
	size_t			i;
	unsigned char	*p;

	if (instruction->param[1].type == IND_CODE)
	{
		i = instruction->param[1].value;
		p = cpu->memory + process->pc_index + i;
		p[0] = (process->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
		p[1] = (process->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
		p[2] = (process->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
		p[3] = (process->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
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
