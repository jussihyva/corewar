/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:12 by ubuntu            #+#    #+#             */
/*   Updated: 2020/08/05 19:14:56 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static int			read_param(unsigned char **p, int size, int length)
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
			param += ((*p)[c] & 0xff) << (8 * (size - (c + 1)));
		else
			param_short += ((*p)[c] & 0xff) << (8 * (size - (c + 1)));
	}
	if (!length)
		param = (int)param_short;
	*p += size;
	return (param);
}

static void			read_parameters(int coding_byte, int label_size, unsigned char **ptr,
															t_op_param *param)
{
	size_t			i;

	i = -1;
	while (++i < 3)
	{
		param[i].type = (coding_byte >> (2 + (2 * (2 - i)))) & 0x3;
		if (param[i].type == IND_CODE)
			param[i].value = read_param(ptr, IND_SIZE, 0);
		else if (param[i].type == DIR_CODE)
		{
			if (label_size)
				param[i].value = read_param(ptr, IND_SIZE, 0);
			else
				param[i].value = read_param(ptr, DIR_SIZE, 1);
		}
		else if (param[i].type == REG_CODE)
			param[i].value = read_param(ptr, 1, 0);
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

t_instruction		*parse_instruction(t_cpu *cpu, unsigned char *p)
{
	int				opcode;
	int				coding_byte;
	t_instruction	*instruction;

	instruction = (t_instruction *)ft_memalloc(sizeof(*instruction));
	opcode = *p;
	instruction->opcode = opcode;
	instruction->start_index = p - cpu->memory;
	p += 1;
	if (cpu->g_op_tab[opcode].include_coding_byte)
	{
		coding_byte = (char)*p;
		p += 1;
	}
	else
		coding_byte = specal_coding(opcode);
	if (coding_byte != -1)
		read_parameters(coding_byte, cpu->g_op_tab[opcode].label_size, &p,
															instruction->param);
	instruction->length = p - cpu->memory - instruction->start_index;
	return (instruction);
}

t_asm_code			*parse_instructions(t_input *input, t_cpu *cpu,
													unsigned char *file_content)
{
	unsigned char	*end_ptr;
	unsigned char	*ptr;
	t_asm_code		*asm_code;
	t_instruction	*instruction;
	t_list			*elem;

	asm_code = initialize_asm_code(file_content, input->file_content_size);
	end_ptr = cpu->memory + MEM_SIZE;
	ptr = file_content + sizeof(*asm_code->header);
	while (ptr < end_ptr)
	{
		if (*ptr > 0 && *ptr < 17)
		{
			instruction = parse_instruction(cpu, ptr);
			elem = ft_lstnew(&instruction, sizeof(instruction));
			ft_lstadd_e(asm_code->instruction_lst, elem);
			ptr += instruction->length;
		}
		else
		{
			ft_printf("%08x: .\n", ptr);
			ptr++;
		}
	}
	return (asm_code);
}
