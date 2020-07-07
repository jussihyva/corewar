/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/07 10:57:27 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void			execute_cpu_cycles(t_input *input, t_cpu *cpu)
{
	size_t			num_of_players_alive;
	t_player		*player;
	int				i;

	i = -1;
	while (++i < input->num_of_players)
	{
		player = input->players[i];
		player->next_instruction = parse_instruction(cpu, player->pc);
		player->cycle_point_for_next_instruction = cpu->cycle_cnt +
						cpu->g_op_tab[player->next_instruction->opcode].cycles;
	}
	i = 0;
	num_of_players_alive = input->num_of_players;
	while (num_of_players_alive)
	{
		num_of_players_alive = execute_cycle(cpu, input->players, input->num_of_players);
		if (input->num_of_instructions_to_execute != -1)
			input->num_of_instructions_to_execute--;
	}
	return ;
}

int					main(int argc, char **argv)
{
	t_input			*input;
	t_cpu			*cpu;

	ft_step_args(&argc, &argv);
	input = read_input_data(&argc, &argv);
	if (input->num_of_players)
	{
		cpu = initialize_cpu(input);
		execute_cpu_cycles(input, cpu);
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
