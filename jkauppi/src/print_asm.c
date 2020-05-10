/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/10 18:55:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static t_header		*read_header(char *file_content)
{
	t_header	*header;

	header = (t_header *)ft_memalloc(sizeof(*header));
	ft_memcpy(header, file_content, sizeof(*header));
	ft_printf("Name:    %s\n", header->prog_name);
	ft_printf("Comment: %s\n", header->comment);
	ft_printf("Magic:   %x\n", header->magic);
	ft_printf("Size:    %x\n", header->prog_size);
	return (header);
}

static void			read_parameters(int coding_byte, int label_size, char **p)
{
	int				param_type[3];
	size_t			i;

	i = -1;
	while (++i < 3)
	{
		param_type[i] = (coding_byte >> (2 + (2 * (2 - i)))) & 0x3;
		if (param_type[i] == 3)
			*p += 2;
		else if (param_type[i] == 2)
		{
			if (label_size)
				*p += 2;
			else
				*p += 4;
		}
		else if (param_type[i] == 1)
			*p += 1;
		ft_printf("  param%d:  %02d", i + 1, param_type[i]);
	}
	return ;
}

static void			specal_coding(int opcode, char **p)
{
	*p += (opcode == e_live) ? 4 : 0;
	*p += (opcode == e_zjmp) ? 2 : 0;
	*p += (opcode == e_fork) ? 2 : 0;
	return ;
}

static void			parse(t_input *input, char **p, int *dot_added)
{
	int		opcode;
	int		coding_byte;

	if (*dot_added)
		ft_printf("\n");
	*dot_added = 0;
	coding_byte = -1;
	opcode = **p;
	ft_printf("OPCODE: %s", input->g_op_tab[opcode].instruction_name);
	*p += 1;
	if (input->g_op_tab[opcode].include_coding_byte)
	{
		coding_byte = (char)**p;
		ft_printf("  coding_byte:  %02hhx", coding_byte);
		*p += 1;
	}
	if (coding_byte == -1)
		specal_coding(opcode, p);
	else
		read_parameters(coding_byte, input->g_op_tab[opcode].label_size, p);
	ft_printf("\n");
	return ;
}

void				print_asm(t_input *input, char *file_content, ssize_t size)
{
	t_header	*header;
	char		*p;
	char		*end_p;
	int			dot_added;

	header = read_header(file_content);
	end_p = file_content + size;
	dot_added = 0;
	p = file_content + sizeof(*header);
	while (p < end_p)
	{
		if (*p > 0 && *p < 17)
			parse(input, &p, &dot_added);
		else
		{
			dot_added = 1;
			ft_printf(".");
			p++;
		}
	}
	free(header);
	return ;
}
