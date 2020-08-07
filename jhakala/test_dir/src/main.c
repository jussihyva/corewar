/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:13:41 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/07 21:21:38 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

void print_p(t_player *p) //
{
	ft_printf("p->id='%d'\n", p->id);
	ft_printf("p->file_name='%s'\n", p->file_name);
	ft_printf("p->input='%s'\n", p->input);
}

void pri(t_mem *mem) //
{
	t_player *p;

	ft_printf("dump='%d'\n", mem->dump);
	ft_printf("n_player='%d'\n", mem->n_player);
	p = mem->player;
	while (p)
	{
		ft_printf("file_name='%s'\n", p->file_name);
		ft_printf("id='%d'\n", p->id);
		p = p->next;
	}
}

// makefile gcc # -Wall -Wextra -Werror
/*
int		main(int ac, char **av)
{
	t_mem *mem;

	if (ac < 2)
		return(printf("usage: ./prog bla bla bla... print usage and flags like
		original ./corewar does\n"));
	if ((mem = ft_init(ac, av)) == NULL)
		return (0);
	else if ((mem->game = wm_init(mem)) == NULL)
		return (0);
	else if (!run_game(mem))
		ft_printf("Contestant %d, \"%s\", has won !\n",
		mem->game->last_alive->id, mem->game->last_alive->header->prog_name);
	free_memory(mem);
	return (0);
}
*/

int		main(int ac, char **av)
{
	t_mem *mem;

	if (ac < 2)
	{
		ft_printf("usage: ./prog bla bla bla... print usage and flags like original ./corewar does\n");
		return (0);
	}
	if ((mem = ft_init(ac, av)) == NULL)
	{
		ft_printf("______________PAASI LOPPUUN!_____error1________\n");
		system("leaks prog");
		return (0);
	}
	else if ((mem->game = wm_init(mem)) == NULL)
	{
		ft_printf("______________PAASI LOPPUUN!_____error2________\n");
		system("leaks prog");
		return (0);
	}
	else if (!run_game(mem))
	{
		ft_printf("Contestant %d, \"%s\", has won !\n", mem->game->last_alive->id,
				  mem->game->last_alive->header->prog_name);
	}
//	pri(mem);
//	print_c_lst(mem->game->c_lst);
	free_memory(mem);
//	ft_printf("______________PAASI LOPPUUN!_______good______\n");
//	system("leaks prog");
	return (0);
}
