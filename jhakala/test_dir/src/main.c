/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:13:41 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/17 17:39:02 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

/*
int main(int ac, char **av)
{
	char *line;
//	char buf[sizeof(int)];
	unsigned int buf;
	unsigned char des[4];
	unsigned char *tmp;
	int fd;
	unsigned int i = 0;


	if (ac > 0)
	{
		fd = open(av[1], O_RDONLY);
		read(fd, &buf, sizeof(buf));
		ft_printf("buf = '%x'\n", buf);
		i = buf >> 24;
		i += buf << 24;
		i += (((buf >> 16) << 24) >> 16);
		i += (((buf >> 8) << 24) >> 8);
		ft_printf("i = '%x'\n", i);
		ft_printf("REV = '%x'\n", REV(buf));
		if (buf == COREWAR_EXEC_MAGIC)
			ft_printf("EKA\n");
		if (REV(buf) == COREWAR_EXEC_MAGIC)
			ft_printf("TOKA\n");
		ft_printf("EXEC_MA = '%x'\n", COREWAR_EXEC_MAGIC);
		
//		for (int j = 0; j < sizeof(des); j++)
//		{
//			ft_printf("%02x ", des[j]);
//			ft_printf("%02x ", des[j]);
//		}
//
	}
	return (0);
}
*/

void pri(t_mem *mem)
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

int		main(int ac, char **av)
{
	t_mem *mem;

	if (ac > 0)
	{
		if ((mem = ft_init(ac, av)) == NULL)
		{
			system("leaks prog");
			ft_printf("______________PAASI LOPPUUN!_____error1________\n");
			return (0);
		}
		else if ((mem->game = wm_init(mem)) == NULL)
		{
			system("leaks prog");
			ft_printf("______________PAASI LOPPUUN!_____error2________\n");
			return (0);
		}
		pri(mem);
	}
	ft_printf("______________PAASI LOPPUUN!_______good______\n");
	free_memory(mem);
	system("leaks prog");
	return (0);
}
