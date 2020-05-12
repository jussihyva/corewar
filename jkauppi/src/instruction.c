/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/11 13:17:12 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 08:27:44 by ubuntu           ###   ########.fr       */
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
		if (param[i].type == 3)
			param[i].value = read_param(p, 2, 0);
		else if (param[i].type == 2)
		{
			if (label_size)
				param[i].value = read_param(p, 2, 0);
			else
				param[i].value = read_param(p, 4, 1);
		}
		else if (param[i].type == 1)
			param[i].value = read_param(p, 1, 0);
	}
	return ;
}

void				print_params(t_op_param *param)
{
	size_t		i;

	i = -1;
	while (++i < 3)
	{
		if (i > 0 && param[i].type)
			ft_printf(",");
		if (param[i].type == 1)
			ft_printf("r%d", param[i].value);
		else if (param[i].type == 2)
		{
			if (param[i].value < 0)
				ft_printf("%%-%#x", -param[i].value);
			else
				ft_printf("%%%#x", param[i].value);
		}
		else if (param[i].type == 3)
			ft_printf("xxxxxx%d", param[i].value);
	}
	return ;
}

static int			specal_coding(int opcode, char **p)
{
	int			coding_byte;

	(void)p;
	coding_byte = -1;
	if (opcode == e_live)
		coding_byte = 0x80;
	else if (opcode == e_zjmp)
		coding_byte = 0x80;
	else if (opcode == e_fork)
		coding_byte = 0x80;
	return (coding_byte);
}

void				parse_instruction(t_input *input, char **p,
													t_list **instruction_lst)
{
	int				opcode;
	int				coding_byte;
	ssize_t			length;
	char			*start_p;
	t_instruction	*instruction;
	t_list			*elem;

	instruction = (t_instruction *)ft_memalloc(sizeof(*instruction));
	ft_bzero(instruction->param, sizeof(*instruction->param) * 3);
	start_p = *p;
	opcode = **p;
	*p += 1;
	if (input->g_op_tab[opcode].include_coding_byte)
	{
		coding_byte = (char)**p;
		*p += 1;
	}
	else
		coding_byte = specal_coding(opcode, p);
	if (coding_byte != -1)
		read_parameters(coding_byte, input->g_op_tab[opcode].label_size, p,
															instruction->param);
	length = *p - start_p;
	instruction->opcode = opcode;
	instruction->start_p = start_p;
	instruction->length = length;
	elem = ft_lstnew(instruction, sizeof(*instruction));
	ft_lstadd_e(instruction_lst, elem);
}
