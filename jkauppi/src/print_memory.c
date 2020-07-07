/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:31:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/07 10:28:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		print_memory(t_cpu *cpu)
{
	char		*ptr;
	char		*end_ptr;
	int			c;

	ptr = cpu->memory;
	end_ptr = cpu->memory + MEM_SIZE;
	c = 0;
	while (ptr < end_ptr)
	{
		if (!(c % 32) && c != 0)
			ft_printf("\n");
		if (!(c % 32))
			ft_printf("0x%0.4x: ", ptr - cpu->memory);
		ft_printf(" %02.2hhx", *ptr);
		ptr++;
		c++;
	}
	if (((c - 1) % 32) && c != 0)
		ft_printf("\n");
	return ;
}
