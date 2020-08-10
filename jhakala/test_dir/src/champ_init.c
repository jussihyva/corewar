/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   champ_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 14:35:03 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 02:30:44 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		pick(int *n_arr, int n)
{
	int i;

	i = n;
	while (--i > -1)
	{
		if (n_arr[i] == 0)
		{
			n_arr[i]++;
			return (i + 1);
		}
	}
	return (0);
}

void	new_player(t_player **alst, char *str, int number)
{
	t_player *new;
	t_player *tmp;
	t_player *prev;

	new = (t_player*)malloc(sizeof(t_player));
	new->file_name = str;
	new->id = number;
	new->header = NULL;
	new->input = NULL;
	tmp = *alst;
	prev = NULL;
	while (tmp && new->id > tmp->id)
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!prev)
		*alst = new;
	else
		prev->next = new;
	new->next = tmp;
}

int		champ_init(int *arg, int n, int *n_arr, t_mem *mem)
{
	int i;
	int tmp;

	if (!n_arr)
		return (1);
	i = n;
	while (--i > -1)
	{
		if (arg[i] == 5)
		{
			if (i > 1 && arg[i - 2] == 3)
				new_player(&mem->player, mem->av[i + 1], ft_atoi(mem->av[i]));
			else
			{
				if ((tmp = pick(n_arr, mem->n_player)) == 0)
					return (free_int(n_arr));
				new_player(&mem->player, mem->av[i + 1], tmp);
			}
		}
	}
	if (read_to(mem))
		return (free_int(n_arr));
	free(n_arr);
	return (0);
}
