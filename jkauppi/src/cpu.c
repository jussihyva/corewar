/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/06 18:22:23 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

static int			execute_instruction(t_cpu *cpu, t_input *input)
{
	if (execute_cycle(cpu, input->players, input->num_of_players))
		return (0);
	return (1);
}

static void			execute_instructions(t_player *player, t_input *input,
																	t_cpu *cpu)
{
//	t_instruction	*instruction;
	int				i;

	i = -1;
	while (++i < input->num_of_players)
		input->players[i]->next_instruction = parse_instruction(cpu,
														input->players[i]->pc);
	i = 0;
	while (*input->players[i]->next_instruction->start_p > 0 && input->num_of_instructions_to_execute &&
			*input->players[i]->next_instruction->start_p < 17 && player->pc == input->players[i]->next_instruction->start_p)
	{
		if (execute_instruction(cpu, input))
		{
			// ft_printf("%08x: %s\n", player->pc - cpu->memory,
			// 			input->g_op_tab[instruction->opcode].instruction_name);
			break ;
		}
		// if (input->opt & verbose)
		// 	print_cpu(cpu, input, player, input->players[i]->next_instruction);
		// free(instruction);
		// instruction = parse_instruction(cpu, player->pc);
		if (input->num_of_instructions_to_execute != -1)
			input->num_of_instructions_to_execute--;
	}
	ft_printf("Player %d killed.\n", player->player_number);
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
