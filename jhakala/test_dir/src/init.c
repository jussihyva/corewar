/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:18:17 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 20:58:33 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	default_values(char **av, t_mem *mem)
{
	mem->av = av;
	mem->dump = -1;
	mem->dump_type = 32;
	mem->n_player = 0;
	mem->player = NULL;
	mem->game = NULL;
	mem->print = 0;
	mem->leaks = 0;
}

t_mem	*ft_init(int ac, char **av)
{
	t_mem	*mem;

	if (!(mem = (t_mem*)malloc(sizeof(t_mem))))
		return (NULL);
	default_values(av, mem);
	if (parse_av(ac, av, mem) == 1)
	{
		ft_mem_return("Mem init error.\n", 0, mem);
		exit(0);
	}
	return (mem);
}
