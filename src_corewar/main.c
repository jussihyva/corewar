/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:13:41 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/16 21:52:34 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		ft_return(char *line, int ret)
{
	ft_putstr_fd(line, 2);
	return (ret);
}

int		ft_mem_return(char *line, int ret, t_mem *mem)
{
	ft_putstr_fd(line, 2);
	if (free_memory(mem))
		system("leaks corewar");
	return (ret);
}

/*
** -dump/-d [n]: print arena after n cycles
** -n [n]: set player number
** -print: print wm run
** -f: leaks
** -v: ncurses
*/

int		main(int ac, char **av)
{
	t_mem	*mem;

	if (ac < 2)
	{
		ft_printf("usage: ./corewar [-dump/-d 123] [-print] [-n 1] .cor...\n");
		return (0);
	}
	if ((mem = ft_init(ac, av)) == NULL)
		return (ft_return("Mem init error.\n", 0));
	else if ((mem->game = wm_init(mem)) == NULL)
		return (ft_mem_return("Game init error.\n", 0, mem));
	else if (!run_game(mem) && mem->ncurses == 0)
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
				mem->game->last_alive->id,
				mem->game->last_alive->header->prog_name);
	}
	if (mem->ncurses == 1)
	{
		print_ncurses_end(mem);
		endwin();
	}
	if (free_memory(mem))
		system("leaks corewar");
	return (0);
}
