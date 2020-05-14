/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/14 12:09:13 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

static t_input		*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(argc, argv);
	input = (t_input *)ft_memalloc(sizeof(input));
	read_g_op_tab(input);
	fd = 0;
	input->file_content = read_input_file(fd, &input->file_content_size);
	return (input);
}

int					main(int argc, char **argv)
{
	t_input			*input;
	t_asm_code		*asm_code;
	t_instruction	*instruction;
	t_cpu			*cpu;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	input = read_input_data(&argc, &argv);
	asm_code = parse_instructions(input, input->file_content,
													input->file_content_size);
	cpu->PC = asm_code->file_content + sizeof(*asm_code->header);
	instruction = parse_instruction(input, cpu->PC);
	while (*instruction->start_p > 0 && *instruction->start_p < 17)
	{
		if (cpu->PC == instruction->start_p)
		{
			if (instruction->opcode == e_live)
				exec_live(cpu, instruction, asm_code);
			else if (instruction->opcode == e_ld)
				exec_ld(cpu, instruction, asm_code);
			else if (instruction->opcode == e_zjmp)
				exec_zjmp(cpu, instruction, asm_code);
			else if (instruction->opcode == e_sti)
				exec_sti(cpu, instruction, asm_code);
			else if (instruction->opcode == e_ldi)
				exec_ldi(cpu, instruction, asm_code);
			else if (instruction->opcode == e_sub)
				exec_sub(cpu, instruction, asm_code);
			else if (instruction->opcode == e_add)
				exec_add(cpu, instruction, asm_code);
			else if (instruction->opcode == e_or)
				exec_or(cpu, instruction, asm_code);
			else if (instruction->opcode == e_and)
				exec_and(cpu, instruction, asm_code);
			else
			{
				ft_printf("%08x: %s\n", cpu->PC - asm_code->file_content,
						input->g_op_tab[instruction->opcode].instruction_name);
				break ;
			}
		}
		else
		{
			ft_printf("%p != %p\n", cpu->PC, instruction->start_p);
			break ;
		}
		instruction = parse_instruction(input, cpu->PC);
	}
	return (0);
}
