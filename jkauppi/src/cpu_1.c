/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:50:37 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/22 17:26:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			*set_op_functions(void)
{
	void	(**op_function)(t_process *, t_instruction *);

	op_function = (void (**)(t_process *process, t_instruction *instruction))
										ft_memalloc(sizeof(*op_function) * 17);
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

static t_process	*initialize_process(t_x_player *x_player, char *pc)
{
	t_process		*process;

	process = (t_process *)ft_memalloc(sizeof(*process));
	process->process_id = x_player->player_number;
	process->pc = pc;
	ft_memcpy(pc, x_player->asm_code->asa_code,
											x_player->asm_code->asa_code_size);
	process->program_start_ptr = process->pc;
	process->reg[1] = -process->process_id;
//	process->asm_code = initialize_asm_code(x_player->file_content, x_player->file_content_size);
	return (process);
}

t_cpu				*initialize_cpu(t_input *input)
{
	t_cpu			*cpu;
	t_x_player		*x_player;
	int				i;
	char			*pc;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	cpu->memory = (char *)ft_memalloc(sizeof(*cpu->memory) * MEM_SIZE);
	cpu->op_function = set_op_functions();
	cpu->g_op_tab = input->g_op_tab;
	cpu->opt = input->opt;
	cpu->current_cycle_to_die = CYCLE_TO_DIE;
	cpu->current_number_of_checks = 0;
	cpu->cycle_cnt = 0;
	cpu->cycle_to_die_point = set_cycle_to_die_point(cpu);
	i = -1;
	while (++i < input->num_of_players)
	{
		x_player = input->x_players[i];
		pc = cpu->memory + (MEM_SIZE / input->num_of_players * i);
		input->process_list[i] = initialize_process(x_player, pc);
	}
	return (cpu);
}
