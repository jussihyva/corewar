/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu_1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 17:50:37 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/07 13:39:32 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			*set_op_functions(void)
{
	void	(**op_function)(t_player *, t_instruction *);

	op_function = (void (**)(t_player *player, t_instruction *instruction))
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

t_cpu		*initialize_cpu(t_input *input)
{
	t_cpu			*cpu;
	t_player		*player;
	char			*mem_position;
	int				i;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	cpu->memory = (char *)ft_memalloc(sizeof(*cpu->memory) * MEM_SIZE);
	cpu->op_function = set_op_functions();
	cpu->g_op_tab = input->g_op_tab;
	cpu->opt = input->opt;
	cpu->current_cycle_to_die = CYCLE_TO_DIE;
	cpu->current_number_of_checks = 0;
	cpu->cycle_cnt = 0;
	cpu->next_cycle_to_die_point = cpu->cycle_cnt + cpu->current_cycle_to_die;
	i = -1;
	while (++i < input->num_of_players)
	{
		player = input->players[i];
		mem_position = cpu->memory + (MEM_SIZE / input->num_of_players * i);
		ft_memcpy(mem_position, player->asm_code->asa_code,
											player->asm_code->asa_code_size);
		player->pc = mem_position;
		player->program_start_ptr = mem_position;
		player->reg[1] = -player->player_number;
	}
	return (cpu);
}
