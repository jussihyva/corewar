/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 11:44:17 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 17:36:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

t_asm_code		*initialize_asm_code(t_input *input, char *file_content)
{
	t_asm_code		*asm_code;

	asm_code = (t_asm_code *)ft_memalloc(sizeof(*asm_code));
	asm_code->instruction_lst =
					(t_list **)ft_memalloc(sizeof(*asm_code->instruction_lst));
	asm_code->header = read_header(file_content);
	asm_code->file_content = file_content;
	asm_code->g_op_tab = input->g_op_tab;
	return (asm_code);
}

t_header		*read_header(char *file_content)
{
	t_header	*header;

	header = (t_header *)ft_memalloc(sizeof(*header));
	ft_memcpy(header, file_content, sizeof(*header));
	return (header);
}

void			print_params(t_op_param *param)
{
	size_t		i;

	i = -1;
	while (++i < 3)
	{
		if (i > 0 && param[i].type)
			ft_printf(", ");
		if (param[i].type == REG_CODE)
			ft_printf("r%d", param[i].value);
		else if (param[i].type == DIR_CODE)
		{
			if (param[i].value < 0)
				ft_printf("%%-%#x", -param[i].value);
			else
				ft_printf("%%%#x", param[i].value);
		}
		else if (param[i].type == IND_CODE)
		{
			if (param[i].value < 0)
				ft_printf("-%#x", -param[i].value);
			else
				ft_printf("%#x", param[i].value);
		}
	}
	return ;
}

void			print_instruction(t_input *input, t_instruction *instruction,
															char *file_content)
{
	ft_printf("%08x: ", instruction->start_p - file_content);
	print_hex_string(0, instruction->start_p, instruction->length);
	ft_printf("%-8s",
					input->g_op_tab[instruction->opcode].instruction_name);
	print_params(instruction->param);
	ft_printf("\n");
	return ;
}
