/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:54:00 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 17:10:14 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		check_dump(int *arg, int n, t_mem *mem, int *i)
{
	int res;

	if (mem->dump != -1)
		return (1);
	if (*i + 1 >= n)
		return (1);
	if (arg[*i + 1] != 4)
		return (1);
	res = ft_atoi(mem->av[*i + 2]);
	if (res < 0)
		return (1);
	mem->dump = res;
	(*i)++;
	return (0);
}

int		check_n(int *arg, int n, t_mem *mem, int *i)
{
	if (*i + 2 >= n)
		return (1);
	if (arg[*i + 1] != 4)
		return (1);
	if (arg[*i + 2] != 5)
		return (1);
	(*i) += 2;
	mem->n_player++;
	return (0);
}
