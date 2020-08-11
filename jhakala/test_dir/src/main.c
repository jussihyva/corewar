/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:13:41 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/11 17:22:52 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int		ft_return(char *line, int ret)
{
	ft_printf("%s", line);
	system("leaks prog");
	return (ret);
}

/*
** -dump [n]: print arena after n cycles
** -n [n]: set player number
** -print: print wm run
*/

int		main(int ac, char **av)
{
	t_mem *mem;

	if (ac < 2)
		return (ft_return("usage: ./corewar [-dump 123] [-n 1] .cor...\n", 0));
	if ((mem = ft_init(ac, av)) == NULL)
		return (ft_return("error1\n", 0));
	else if ((mem->game = wm_init(mem)) == NULL)
		return (ft_return("error2\n", 0));
	else if (!run_game(mem))
	{
		ft_printf("Contestant %d, \"%s\", has won !\n",
				mem->game->last_alive->id,
				mem->game->last_alive->header->prog_name);
	}
//	ft_printf("here\n");
//	free_memory(mem);
//	system("leaks prog");
	return (0);
}
