/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:01:15 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 21:38:27 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		whole_number(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (1);
		i++;
	}
	return (0);
}

int		*check_numbers_after_n(int ac, char **av, int *arg, t_mem *mem)
{
	int i;
	int tmp;
	int *n_arr;

	n_arr = (int*)malloc(sizeof(int) * (mem->n_player));
	i = 0;
	while (i <= mem->n_player)
		n_arr[i++] = 0;
	i = -1;
	while (++i < ac - 1)
	{
		if (arg[i] == 3)
		{
			tmp = ft_atoi(av[i + 1]);
			if (tmp > 0 && tmp <= mem->n_player && n_arr[tmp - 1] < 1)
				n_arr[tmp - 1]++;
			else
			{
				free(n_arr);
				return (NULL);
			}
		}
	}
	return (n_arr);
}

int		check_av(int *arg, int n, t_mem *mem)
{
	int i;
	int check;

	i = -1;
	check = 0;
	if (arg[0] == 1)
	{
		if (arg[1] == 1)
			i = 1;
		else
			return (1);
	}
	while (++i < n)
	{
		if (arg[i] == 4 && (check == 0 || check == 2))
		{
			check = 0;
			mem->n_player++;
		}
		else if (arg[i] == 2 && check == 0)
			check = 1;
		else if (arg[i] == 3 && check == 1)
			check = 2;
		else
			return (1);
	}
	return (check == 0 ? 0 : 1);
}

void	parse_to_arg(int ac, char **av, t_mem *mem, int *arg)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	if (ac > 2 && !ft_strcmp(av[1], "-dump") && !whole_number(av[2]))
	{
		mem->dump = ft_atoi(av[2]);
		arg[0] = 1;
		arg[1] = 1;
		i = 2;
	}
	if (!ft_strcmp(av[3], "-print"))
	{
		mem->print = 1;
		i = 3;
	}
	while (++i < ac)
	{
		arg[i - 1] = 0;
		if (!ft_strcmp(av[i], "-n"))
			arg[i - 1] = 2;
		else if (!whole_number(av[i]))
			arg[i - 1] = 3;
		else
		{
			if ((len = ft_strlen(av[i])) > 4)
			{
				name = &av[i][len - 4];
				if (!ft_strcmp(name, ".cor"))
					arg[i - 1] = 4;
			}
		}
	}
}

int		parse_av(int ac, char **av, t_mem *mem)
{
	int *arg;

	arg = (int*)malloc(sizeof(int) * (ac - 1));
	parse_to_arg(ac, av, mem, arg);
	if (check_av(arg, ac - 1, mem) || mem->n_player < 1 || mem->n_player >
		MAX_PLAYERS)
		return (free_int(arg));
	if (champ_init(arg, ac - 1, check_numbers_after_n(ac, av, arg, mem), mem))
		return (free_int(arg));
	free(arg);
	return (0);
}
