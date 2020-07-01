/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 17:31:57 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/01 11:26:52 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void		print_memory(t_cpu *cpu)
{
	char		*ptr;
	char		*end_ptr;
	int			c;

	ptr = cpu->program_start_ptr;
	end_ptr = cpu->program_start_ptr + MEM_SIZE;
	c = 0;
	while (ptr < end_ptr)
	{
		if (!(c % 32) && c != 0)
			ft_printf("\n");
		if (!(c % 32))
			ft_printf("0x%0.4x: ", ptr - cpu->program_start_ptr);
		ft_printf(" %02.2hhx", *ptr);
		ptr++;
		c++;
	}
	if (((c - 1) % 32) && c != 0)
		ft_printf("\n");
	return ;
}
