/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_av.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 13:01:15 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 20:59:22 by jhakala          ###   ########.fr       */
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
		else if (arg[i] == 6)
			mem->leaks = 1;
		else
			return (1);
		if (check == 1)
			return (1);
	}
	return (0);
}

void	parse_to_arg(int ac, char **av, int *arg, t_mem *mem)
{
	int		i;
	int		len;
	char	*name;

	i = 0;
	while (++i < ac)
	{
		arg[i - 1] = 0;
		if (check_flag(i, arg, av, mem) == 1)
			continue ;
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
	parse_to_arg(ac, av, arg, mem);
	if (check_av(arg, ac - 1, mem) || mem->n_player < 1 || mem->n_player >
		MAX_PLAYERS)
		return (free_int(arg));
	if (champ_init(arg, ac - 1, check_numbers_after_n(ac, av, arg, mem), mem))
		return (free_int(arg));
	free(arg);
	return (0);
}
