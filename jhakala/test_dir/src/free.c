/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:11:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/17 16:34:30 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		free_int(int *arr)
{
	free(arr);
	return (1);
}

int		free_memory(t_mem *mem)
{
	t_player *p;
	t_player *tmp;

	p = mem->player;
	while (p)
	{
		if (p->header)
			free(p->header);
		if (p->input)
			free(p->input);
		tmp = p;
		p = p->next;
		free(tmp);
	}
	free(mem);
	return (1);
}
