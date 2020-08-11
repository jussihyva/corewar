/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:01:15 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 14:38:59 by hopham           ###   ########.fr       */
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
			tmp = ft_atoi(av[i + 2]);
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
	while (++i < n)
	{
		if (arg[i] == 1)
			check = check_dump(arg, n, mem, &i);
		else if (arg[i] == 2)
			mem->print = 1;
		else if (arg[i] == 3)
			check = check_n(arg, n, mem, &i);
		else if (arg[i] == 5)
			mem->n_player++;
		else
			return (1);
		if (check == 1)
			return (1);
	}
	return (0);
}

// arg[i] values: -dump = 1, -print = 2, -n = 3, contains_only_numbers = 4, .cor file = 5, if = 0 undefined and error

void	parse_to_arg(int ac, char **av, int *arg)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	while (++i < ac)
	{
		arg[i - 1] = 0;
		if (!ft_strcmp(av[i], "-dump"))
			arg[i - 1] = 1;
		else if (!ft_strcmp(av[i], "-print"))
			arg[i - 1] = 2;
		else if (!ft_strcmp(av[i], "-n"))
			arg[i - 1] = 3;
		else if (!whole_number(av[i]))
			arg[i - 1] = 4;
		else
		{
			if ((len = ft_strlen(av[i])) > 4)
			{
				if (!ft_strcmp((name = &av[i][len - 4]), ".cor"))
					arg[i - 1] = 5;
			}
		}
	}
}

int		parse_av(int ac, char **av, t_mem *mem)
{
	int *arg;

	arg = (int*)malloc(sizeof(int) * (ac - 1));
	parse_to_arg(ac, av, arg);
	if (check_av(arg, ac - 1, mem) || mem->n_player < 1 || mem->n_player >
		MAX_PLAYERS)
		return (free_int(arg));
	if (champ_init(arg, ac - 1, check_numbers_after_n(ac, av, arg, mem), mem))
		return (free_int(arg));
	free(arg);
	return (0);
}
