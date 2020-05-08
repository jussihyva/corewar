/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/08 19:26:32 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static t_header		*read_header(char *file_content, ssize_t size)
{
	t_header	*header;

	(void)size;
	header = (t_header *)ft_memalloc(sizeof(*header));
	ft_memcpy(header, file_content, sizeof(*header));
	return (header);
}

static void			read_parameters(int coding_byte, char **p)
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
			*p += 4;
		else if (param_type[i] == 1)
			*p += 1;
		ft_printf("  param%d:  %02d", i + 1, param_type[i]);
	}
	ft_printf("\n");
	return ;
}

static void			parse_live(char **p)
{
	ft_printf("OPCODE:  %02x\n", **p);
	*p += 1;
	*p += 4;
	return ;
}

static void			parse_ld(char **p)
{
	int				coding_byte;

	ft_printf("OPCODE:  %02x\n", **p);
	*p += 1;
	coding_byte = (char)**p;
	ft_printf("  coding_byte:  %02hhx\n", coding_byte);
	*p += 1;
	read_parameters(coding_byte, p);
	return ;
}

void				print_asm(char *file_content, ssize_t size)
{
	t_header	*header;
	char		*p;
	char		*end_p;

	header = read_header(file_content, size);
	ft_printf("Name:    %s\n", header->prog_name);
	ft_printf("Comment: %s\n", header->comment);
	ft_printf("Magic:   %x\n", header->magic);
	ft_printf("Size:    %x\n", header->prog_size);
	end_p = file_content + size;
	p = file_content + sizeof(*header);
	while (p < end_p)
	{
		if (*p == e_live)
			parse_live(&p);
		else if (*p == e_ld)
			parse_ld(&p);
		else if (*p == e_zjmp)
			parse_live(&p);
		else
			p++;
	}
	return ;
}
