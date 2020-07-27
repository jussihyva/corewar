/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 23:35:12 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/27 15:05:21 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	n_error(char *str, int *op)
{
	ft_printf("%s", str);
	if (op[20] == 1)
		system("leaks asm");
	free(op);
}

int		*o_error(char *str, int *op)
{
	ft_printf("%s", str);
	if (op[20] == 1)
		system("leaks asm");
	free(op);
	return (NULL);
}

int		*fill(char *str, int *op)
{
	int i;
	int check;

	check = 0;
	if (str[0] != '-')
		return(o_error("Missing '-' before flag(s).\n", op));
	i = 0;
	while (str[++i])
	{
		if (str[i] == 'h')
			check = 1;
		if (is_that_char(str[i], OPTION_CHARS) == 0)
			return(o_error("Invalid flag char(s)\n", op));
	}
	if (check == 1)
		return(o_error("usage: ./asm [-f] source_file\n", op));
	i = 0;
	while (str[++i])
		op[122 - str[i]] = 1;
	return (op);
}

int		*options(char *str)
{
	int	*op;
	int i;

	if (!(op = (int*)malloc(sizeof(int) * 26)))
	{
		ft_printf("Malloc error.\n");
		exit(0);
	}
	i = 0;
	while (i < 26)
		op[i++] = 0;
	if (str[0] == '\0')
		return (op);
	return (fill(str, op));
}

/*
** use ./asm -d source_file.s for saving to asm directory, without -d, asm will save it to original .s directory
** -h: usage
** -f: leaks
*/

int		main(int ac, char **av)
{
	int			fd;
	int			*op;

	if (ac < 2 || ac > 3)
		ft_printf("Invalid argument count\n");
	else
	{
		if (ac == 2 && ft_strcmp("-h", av[1]) == 0)
			ft_printf("usage: ./asm [-f] source_file\n");
		else if (ac == 2 && (fd = open(av[1], O_RDONLY)) > 0 && (op = options("")) != NULL)
			init_champ(fd, op, av[1]);
		else if (ac == 3 && (fd = open(av[2], O_RDONLY)) > 0 && (op = options(av[1])) != NULL)
			init_champ(fd, op, av[2]);
		else if (fd == -1 && ac == 2)
			ft_printf("ERROR: Can't read source file %s\n", av[1]);
		else if (fd == -1 && ac == 3)
			ft_printf("ERROR: Can' t read source file %s\n", av[2]);
	}

	return (0);
}
