/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 11:44:17 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 11:47:17 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

t_header			*read_header(char *file_content)
{
	t_header	*header;

	header = (t_header *)ft_memalloc(sizeof(*header));
	ft_memcpy(header, file_content, sizeof(*header));
	ft_printf("Name: %s", header->prog_name);
	ft_printf(" Comment: %s", header->comment);
	ft_printf(" Magic: %x", header->magic);
	ft_printf(" Size: %x\n", header->prog_size);
	return (header);
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
