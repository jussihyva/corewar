/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:50:37 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/30 16:34:58 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			*set_op_functions(void)
{
	void	(**op_function)(t_cpu *cpu, t_process *, t_instruction *);

	op_function = (void (**)(t_cpu *cpu, t_process *process,
			t_instruction *instruction))ft_memalloc(sizeof(*op_function) * 17);
	op_function[e_lfork] = NULL;
	op_function[e_sti] = exec_sti;
	op_function[e_fork] = exec_fork;
	op_function[e_lld] = NULL;
	op_function[e_ld] = exec_ld;
	op_function[e_add] = exec_add;
	op_function[e_zjmp] = exec_zjmp;
	op_function[e_sub] = exec_sub;
	op_function[e_ldi] = exec_ldi;
	op_function[e_or] = exec_or;
	op_function[e_st] = exec_st;
	op_function[e_aff] = NULL;
	op_function[e_live] = exec_live;
	op_function[e_xor] = exec_xor;
	op_function[e_lldi] = NULL;
	op_function[e_and] = exec_and;
	return (op_function);
}

t_cpu				*initialize_cpu(t_input *input)
{
	t_cpu			*cpu;
	t_player		*player;
	int				i;
	char			*pc;
	t_process		*process;
	t_list			*process_elem;
	int				pc_index;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	cpu->memory = (char *)ft_memalloc(sizeof(*cpu->memory) * MEM_SIZE);
	cpu->op_function = set_op_functions();
	cpu->g_op_tab = input->g_op_tab;
	cpu->opt = input->opt;
	cpu->current_cycle_to_die = CYCLE_TO_DIE;
	cpu->cycle_to_die_point = set_cycle_to_die_point(cpu);
	cpu->check_carry =  0b00000001000000000;
	cpu->modify_carry = 0b00000000111110100;
	i = -1;
	while (++i < input->num_of_players)
	{
		player = input->players[i];
		pc_index = MEM_SIZE / input->num_of_players * i;
		pc = cpu->memory + pc_index;
		ft_memcpy(pc, player->asm_code->asa_code,
											player->asm_code->asa_code_size);
		cpu->process_cnt++;
		process = initialize_process(cpu, pc_index);
		process_elem = ft_lstnew(&process, sizeof(process));
		ft_lstadd(&cpu->process_list, process_elem);
	}
	return (cpu);
}
