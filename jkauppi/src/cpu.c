/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/06 14:46:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

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

static t_cpu		*initialize_cpu(t_input *input)
{
	t_cpu			*cpu;
	t_player		*player;
	char			*mem_position;
	int				i;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	cpu->memory = (char *)ft_memalloc(sizeof(*cpu->memory) * MEM_SIZE);
	cpu->op_function = set_op_functions();
	cpu->g_op_tab = input->g_op_tab;
	cpu->current_cycle_to_die = CYCLE_TO_DIE;
	cpu->current_number_of_checks = 0;
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
		player->cycle_cnt = 0;
		player->next_cycle_to_die_point = player->cycle_cnt +
													cpu->current_cycle_to_die;
	}
	return (cpu);
}

static int			execute_instruction(t_cpu *cpu, t_instruction *instruction,
																t_input *input)
{
	int				cycles_to_execute;

	cycles_to_execute = cpu->g_op_tab[instruction->opcode].cycles;
	if (execute_cycles(cycles_to_execute, cpu, input->players[0]))
		return (1);
	if (instruction->opcode)
		cpu->op_function[instruction->opcode](input->players[0], instruction);
	else
	{
		return (1);
	}
	return (0);
}

static void			execute_instructions(t_player *player, t_input *input,
																	t_cpu *cpu)
{
	t_instruction	*instruction;

	instruction = parse_instruction(input, player->pc);
	while (*instruction->start_p > 0 && input->num_of_instructions_to_execute &&
			*instruction->start_p < 17 && player->pc == instruction->start_p)
	{
		if (execute_instruction(cpu, instruction, input))
		{
			ft_printf("%08x: %s\n", player->pc - cpu->memory,
						input->g_op_tab[instruction->opcode].instruction_name);
			break ;
		}
		if (input->opt & verbose)
			print_cpu(cpu, input, player, instruction);
		free(instruction);
		instruction = parse_instruction(input, player->pc);
		if (input->num_of_instructions_to_execute != -1)
			input->num_of_instructions_to_execute--;
	}
	ft_printf("Player %d killed.\n", player->player_number);
	free(instruction);
	return ;
}

int					main(int argc, char **argv)
{
	t_input			*input;
	t_cpu			*cpu;
	t_player		*player;

	ft_step_args(&argc, &argv);
	input = read_input_data(&argc, &argv);
	player = input->players[0];
	if (player->asm_code->file_content)
	{
		cpu = initialize_cpu(input);
		execute_instructions(player, input, cpu);
		print_memory(cpu);
		free(cpu->memory);
		free(cpu->op_function);
		free(cpu);
	}
	release(input);
	if (input->opt & leaks)
		system("leaks cpu");
	return (0);
}
