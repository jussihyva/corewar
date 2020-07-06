/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/06 17:43:46 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void				print_asm(t_input *input, char *file_content, ssize_t size)
{
	t_list			*elem;
	t_instruction	*instruction;
	t_asm_code		*asm_code;
	t_cpu			*cpu;

	cpu = initialize_cpu(input);
	asm_code = parse_instructions(input, cpu, file_content, size);
	ft_printf("Name: %s", asm_code->header->prog_name);
	ft_printf(" Comment: %s", asm_code->header->comment);
	ft_printf(" Magic: %x", asm_code->header->magic);
	ft_printf(" Size: %x\n", asm_code->header->prog_size);
	elem = *asm_code->instruction_lst;
	while (elem)
	{
		instruction = *(t_instruction **)elem->content;
		print_instruction(instruction,
								instruction->start_p - asm_code->file_content,
						input->g_op_tab[instruction->opcode].instruction_name);
		elem = elem->next;
	}
	remove_asm_code(asm_code);
	return ;
}
