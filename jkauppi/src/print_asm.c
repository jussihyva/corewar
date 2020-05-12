/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 12:07:57 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void				print_asm(t_input *input, char *file_content, ssize_t size)
{
	t_list			*elem;
	t_instruction	*instruction;
	t_asm_code		*asm_code;

	asm_code = parse_instructions(input, file_content, size);
	elem = *asm_code->instruction_lst;
	while (elem)
	{
		instruction = *(t_instruction **)elem->content;
		ft_printf("%08x: ", instruction->start_p - file_content);
		print_hex_string(0, instruction->start_p, instruction->length);
		ft_printf("%-8s",
						input->g_op_tab[instruction->opcode].instruction_name);
		print_params(instruction->param);
		ft_printf("\n");
		elem = elem->next;
	}
	return ;
}
