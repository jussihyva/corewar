/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/11 09:42:50 by ubuntu           ###   ########.fr       */
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

static int			read_param(char *p, int size)
{
	int			param;
	int			c;

	param = 0;
	c = -1;
	while (++c < size)
		param |= p[c] << (8 * (size - (c + 1)));
	return (param);
}

static void			print_params(int *param)
{
	size_t		i;

	i = -1;
	while (++i < 3)
		ft_printf(" %d", param[i]);
	return ;
}
static void			read_parameters(int coding_byte, int label_size, char **p,
																	int *param)
{
	int				param_type[3];
	size_t			i;

	i = -1;
	while (++i < 3)
	{
		param_type[i] = (coding_byte >> (2 + (2 * (2 - i)))) & 0x3;
		if (param_type[i] == 3)
		{
			param[i] = read_param(*p, 2);
			*p += 2;
		}
		else if (param_type[i] == 2)
		{
			if (label_size)
			{
				param[i] = read_param(*p, 2);
				*p += 2;
			}
			else
			{
				param[i] = read_param(*p, 4);
				*p += 4;
			}
		}
		else if (param_type[i] == 1)
		{
			param[i] = read_param(*p, 1);
			*p += 1;
		}
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

static void			parse(t_input *input, char **p)
{
	int			opcode;
	int			coding_byte;
	ssize_t		size;
	char		*start_p;
	int			param[3];

	ft_bzero(param, sizeof(int) * 3);
	start_p = *p;
	coding_byte = -1;
	opcode = **p;
	*p += 1;
	if (input->g_op_tab[opcode].include_coding_byte)
	{
		coding_byte = (char)**p;
		*p += 1;
	}
	if (coding_byte == -1)
		specal_coding(opcode, p);
	else
		read_parameters(coding_byte, input->g_op_tab[opcode].label_size, p,
																		param);
	size = *p - start_p;
	print_hex_string(0, start_p, size);
	ft_printf("%-5s", input->g_op_tab[opcode].instruction_name);
	ft_printf("coding_byte:  %02hhx", coding_byte);
	print_params(param);
	return ;
}

void				print_asm(t_input *input, char *file_content, ssize_t size)
{
	t_header	*header;
	char		*p;
	char		*end_p;
	char		*start_p;

	header = read_header(file_content);
	end_p = file_content + size;
	start_p = file_content;
	p = file_content + sizeof(*header);
	while (p < end_p)
	{
		ft_printf("%08x: ", p - start_p);
		if (*p > 0 && *p < 17)
			parse(input, &p);
		else
		{
			ft_printf(".");
			p++;
		}
		ft_printf("\n");
	}
	free(header);
	return ;
}
