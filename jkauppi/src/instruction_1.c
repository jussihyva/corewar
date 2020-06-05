/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:12 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 17:31:37 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static int			read_param(char **p, int size, int length)
{
	int				param;
	short int		param_short;
	int				c;

	param = 0;
	param_short = 0;
	c = -1;
	while (++c < size)
	{
		if (length)
		{
			param += (*p)[c] & 0xff;
			param = param << (8 * (size - (c + 1)));
		}
		else
		{
			param_short += (*p)[c] & 0xff;
			param_short = param_short << (8 * (size - (c + 1)));
		}
	}
	if (!length)
		param = (int)param_short;
	*p += size;
	return (param);
}

static void			read_parameters(int coding_byte, int label_size, char **p,
															t_op_param *param)
{
	size_t			i;

	i = -1;
	while (++i < 3)
	{
		param[i].type = (coding_byte >> (2 + (2 * (2 - i)))) & 0x3;
		if (param[i].type == IND_CODE)
			param[i].value = read_param(p, IND_SIZE, 0);
		else if (param[i].type == DIR_CODE)
		{
			if (label_size)
				param[i].value = read_param(p, IND_SIZE, 0);
			else
				param[i].value = read_param(p, DIR_SIZE, 1);
		}
		else if (param[i].type == REG_CODE)
			param[i].value = read_param(p, 1, 0);
	}
	return ;
}

static int			specal_coding(int opcode)
{
	int			coding_byte;

	coding_byte = -1;
	if (opcode == e_live)
		coding_byte = 0x80;
	else if (opcode == e_zjmp)
		coding_byte = 0x80;
	else if (opcode == e_fork)
		coding_byte = 0x80;
	return (coding_byte);
}

t_instruction		*parse_instruction(t_input *input, char *p)
{
	int				opcode;
	int				coding_byte;
	t_instruction	*instruction;

	instruction = (t_instruction *)ft_memalloc(sizeof(*instruction));
	opcode = *p;
	instruction->opcode = opcode;
	instruction->start_p = p;
	p += 1;
	if (input->g_op_tab[opcode].include_coding_byte)
	{
		coding_byte = (char)*p;
		p += 1;
	}
	else
		coding_byte = specal_coding(opcode);
	if (coding_byte != -1)
		read_parameters(coding_byte, input->g_op_tab[opcode].label_size, &p,
															instruction->param);
	instruction->length = p - instruction->start_p;
	return (instruction);
}

t_asm_code			*parse_instructions(t_input *input, char *file_content,
																ssize_t size)
{
	char			*end_p;
	char			*p;
	t_asm_code		*asm_code;
	t_instruction	*instruction;
	t_list			*elem;

	asm_code = initialize_asm_code(input, file_content);
	end_p = file_content + size;
	p = file_content + sizeof(*asm_code->header);
	while (p < end_p)
	{
		if (*p > 0 && *p < 17)
		{
			instruction = parse_instruction(input, p);
			elem = ft_lstnew(&instruction, sizeof(instruction));
			ft_lstadd_e(asm_code->instruction_lst, elem);
			p = instruction->start_p + instruction->length;
		}
		else
		{
			ft_printf("%08x: .\n", p - file_content);
			p++;
		}
	}
	return (asm_code);
}
