/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 01:54:00 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 20:38:56 by jhakala          ###   ########.fr       */
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

int		check_flag(int i, int *arg, char **av, t_mem *mem)
{
	if (!ft_strcmp(av[i], "-dump"))
		arg[i - 1] = 1;
	if (!ft_strcmp(av[i], "-d"))
	{
		arg[i - 1] = 1;
		mem->dump_type = 64;
	}
	else if (!ft_strcmp(av[i], "-print"))
		arg[i - 1] = 2;
	else if (!ft_strcmp(av[i], "-n"))
		arg[i - 1] = 3;
	else if (!whole_number(av[i]))
		arg[i - 1] = 4;
	else if (!ft_strcmp(av[i], "-f"))
		arg[i - 1] = 6;
	else
		return (0);
	return (1);
}
