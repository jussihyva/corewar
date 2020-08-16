/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:18:17 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/16 21:45:36 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	ncurses_init(t_mem *mem)
{
	initscr();
	cbreak();
	noecho();
	clear();
	timeout(0);
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	mem->dump_type = 64;
	mem->print = 0;
	mem->pause = 1;
	mem->last_key = 0;
	mem->speed = 1;
}

void	default_values(char **av, t_mem *mem)
{
	mem->av = av;
	mem->dump = -1;
	mem->dump_type = 32;
	mem->n_player = 0;
	mem->player = NULL;
	mem->game = NULL;
	mem->print = 0;
	mem->leaks = 0;
	mem->ncurses = 0;
}

t_mem	*ft_init(int ac, char **av)
{
	t_mem	*mem;

	if (!(mem = (t_mem*)malloc(sizeof(t_mem))))
		return (NULL);
	default_values(av, mem);
	if (parse_av(ac, av, mem) == 1)
	{
		ft_mem_return("Mem init error.\n", 0, mem);
		exit(0);
	}
	if (mem->ncurses == 1)
		ncurses_init(mem);
	return (mem);
}
