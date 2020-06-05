/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 17:20:16 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

static void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-v"))
			input->opt |= verbose;
		else if (ft_strequ((*argv)[0], "-f"))
			save_input_file_name(input, argc, argv);
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}

static t_input		*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(argc, argv);
	input = (t_input *)ft_memalloc(sizeof(*input));
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	fd = 0;
	input->file_content = read_input_file(fd, &input->file_content_size);
	return (input);
}

static void			*set_op_functions(void)
{
	void	(**op_function)(t_cpu *, t_instruction *, t_asm_code *);

	op_function = (void (**)(t_cpu *cpu, t_instruction *instruction,
				t_asm_code *asm_code))ft_memalloc(sizeof(*op_function) * 16);
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

static void			execute_instructions(t_input *input, t_cpu *cpu,
														t_asm_code *asm_code)
{
	t_instruction	*instruction;
	void			(**op_function)(t_cpu *, t_instruction *, t_asm_code *);

	op_function = set_op_functions();
	instruction = parse_instruction(input, cpu->pc);
	while (*instruction->start_p > 0 && *instruction->start_p < 17 &&
												cpu->pc == instruction->start_p)
	{
		if (input->opt & verbose)
			print_instruction(input, instruction, asm_code->file_content);
		if (instruction->opcode)
			op_function[instruction->opcode](cpu, instruction, asm_code);
		else
		{
			ft_printf("%08x: %s\n", cpu->pc - asm_code->file_content,
					input->g_op_tab[instruction->opcode].instruction_name);
			break ;
		}
		instruction = parse_instruction(input, cpu->pc);
	}
	ft_printf("%p != %p\n", cpu->pc, instruction->start_p);
	free(op_function);
	return ;
}

int					main(int argc, char **argv)
{
	t_input			*input;
	t_asm_code		*asm_code;
	t_cpu			*cpu;

	cpu = (t_cpu *)ft_memalloc(sizeof(*cpu));
	input = read_input_data(&argc, &argv);
	asm_code = parse_instructions(input, input->file_content,
													input->file_content_size);
	cpu->pc = asm_code->file_content + sizeof(*asm_code->header);
	cpu->program_start_ptr = cpu->pc;
	execute_instructions(input, cpu, asm_code);
	free(input->g_op_tab);
	free(input);
	return (0);
}
