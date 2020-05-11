/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/11 13:22:25 by ubuntu           ###   ########.fr       */
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
			parse_instruction(input, &p);
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
