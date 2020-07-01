/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/01 12:54:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

static void			*set_op_functions(void)
{
	void	(**op_function)(t_cpu *, t_instruction *);

	op_function = (void (**)(t_cpu *cpu, t_instruction *instruction))
										ft_memalloc(sizeof(*op_function) * 16);
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

static t_cpu		*initialize_cpu(t_asm_code *asm_code, t_player *player,
																t_input *input)
{
	t_cpu			*cpu;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	cpu->memory = (char *)ft_memalloc(sizeof(*cpu->memory) * MEM_SIZE);
	ft_memcpy(cpu->memory, asm_code->file_content + sizeof(*asm_code->header),
						input->file_content_size - sizeof(*asm_code->header));
	cpu->g_op_tab = input->g_op_tab;
	cpu->pc = cpu->memory;
	cpu->program_start_ptr = cpu->pc;
	cpu->reg[1] = -player->player_number;
	cpu->current_cycle_to_die = CYCLE_TO_DIE;
	cpu->current_number_of_checks = 0;
	cpu->cycle_cnt = 0;
	cpu->next_cycle_to_die_point = cpu->cycle_cnt + cpu->current_cycle_to_die;
	return (cpu);
}

static int			execute_instruction(t_cpu *cpu, t_instruction *instruction,
				void (**op_function)(t_cpu *, t_instruction *))
{
	int				cycles_to_execute;

	cycles_to_execute = cpu->g_op_tab[instruction->opcode].cycles;
	if (execute_cycles(cycles_to_execute, cpu))
		return (1);
	if (instruction->opcode)
		op_function[instruction->opcode](cpu, instruction);
	else
	{
		return (1);
	}
	return (0);
}

static void			execute_instructions(t_player *player, t_input *input,
											t_cpu *cpu, t_asm_code *asm_code)
{
	t_instruction	*instruction;
	void			(**op_function)(t_cpu *, t_instruction *);

	op_function = set_op_functions();
	instruction = parse_instruction(input, cpu->pc);
	while (*instruction->start_p > 0 && *instruction->start_p < 17 &&
									input->num_of_instructions_to_execute &&
												cpu->pc == instruction->start_p)
	{
		if (execute_instruction(cpu, instruction, op_function))
		{
			ft_printf("%08x: %s\n", cpu->pc - asm_code->file_content,
						input->g_op_tab[instruction->opcode].instruction_name);
			break ;
		}
		if (input->opt & verbose)
			print_cpu(cpu, input, instruction, asm_code);
		instruction = parse_instruction(input, cpu->pc);
		if (input->num_of_instructions_to_execute != -1)
			input->num_of_instructions_to_execute--;
	}
	ft_printf("Player %d killed.\n", player->player_number);
	free(op_function);
	return ;
}

int					main(int argc, char **argv)
{
	t_input			*input;
	t_asm_code		*asm_code;
	t_cpu			*cpu;
	t_player		*player;

	player = (t_player*)ft_memalloc(sizeof(*player));
	ft_step_args(&argc, &argv);
	input = read_input_data(&argc, &argv);
	if (input->file_content)
	{
		player->player_number = input->player_number;
		asm_code = parse_instructions(input, input->file_content,
													input->file_content_size);
		cpu = initialize_cpu(asm_code, player, input);
		execute_instructions(player, input, cpu, asm_code);
		print_memory(cpu);
	}
	free(player);
	free(input->g_op_tab);
	free(input);
	if (input->opt & leaks)
		system("leaks cpu");
	return (0);
}
