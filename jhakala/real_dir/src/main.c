/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 23:35:12 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 01:42:25 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		main(int ac, char **av)
{
	int			fd;
	t_champ		*champ;

	if (ac == 2 && (fd = open(av[1], O_RDONLY)) > 0)
	{
		champ = init_champ(fd);
	}
	system("leaks asm");
	return (0);
}
