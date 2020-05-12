/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 08:27:44 by ubuntu           ###   ########.fr       */
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

void				print_asm(t_input *input, char *file_content, ssize_t size)
{
	t_header		*header;
	char			*p;
	char			*end_p;
	char			*start_p;
	t_list			*instruction_lst;
	t_list			*elem;
	t_instruction	*instruction;

	instruction_lst = NULL;
	header = read_header(file_content);
	end_p = file_content + size;
	start_p = file_content;
	p = file_content + sizeof(*header);
	while (p < end_p)
	{
		if (*p > 0 && *p < 17)
			parse_instruction(input, &p, &instruction_lst);
		else
		{
			ft_printf("%08x: ", p - start_p);
			ft_printf(".");
			ft_printf("\n");
			p++;
		}
	}
	elem = instruction_lst;
	while (elem)
	{
		instruction = (t_instruction *)elem->content;
		ft_printf("%08x: ", instruction->start_p - file_content);
		print_hex_string(0, instruction->start_p, instruction->length);
		ft_printf("%-8s", input->g_op_tab[instruction->opcode].instruction_name);
		print_params(instruction->param);
		ft_printf("\n");
		elem = elem->next;
	}
	free(header);
	return ;
}
