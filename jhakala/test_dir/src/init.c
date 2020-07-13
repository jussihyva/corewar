/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:18:17 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/13 20:02:47 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	new_player(t_player **alst, char *str, int number)
{
	t_player *new;

	new = (t_player*)malloc(sizeof(t_player));
	new->file_name = str;
	new->id = number;
	new->next = *alst;
	*alst = new;
}

int		parse_av(int ac, char **av, t_mem *mem)
{
	int i;
	int len;
	int number;
	char *name;

	i = 1;
	if (!ft_strcmp(av[1], "-dump"))
	{
		mem->dump = ft_atoi(av[++i]);
		i++;
	}
	while (i < ac)
	{
		len = 0;
		if (!ft_strcmp(av[i], "-n"))
		{
			if (++i < ac - 1)
				number = ft_atoi(av[i++]);
			else
			{
				ft_printf("ERROR\n");
				break ;
			}
		}
		if (i < ac)
			len = ft_strlen(av[i]);
		if (len > 4)
		{
			name = &av[i][len - 4];
			if(!ft_strcmp(name, ".cor"))
			{
				new_player(&mem->player, av[i], number);
				mem->n_player++;
				number = -1;
			}
		}
		else
		{
			ft_printf("ERROR\n");
			break ;  // error
		}
		i++;
	}
	return (0);
}

void	default_values(t_mem *mem)
{
	mem->dump = -1;
	mem->n_player = 0;
	mem->player = NULL;
}

t_mem	*ft_init(int ac, char **av)
{
	t_mem *mem;

	mem = (t_mem*)malloc(sizeof(t_mem));
	default_values(mem);
	parse_av(ac, av, mem);
	return (mem);
}
