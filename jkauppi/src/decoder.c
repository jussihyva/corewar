/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:28:48 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/05 14:59:05 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static void			print_hex_string(ssize_t index, char *line, ssize_t size)
{
	ssize_t		end_point;
	ssize_t		i;

	end_point = index + 16;
	i = index;
	while (i < end_point)
	{
		if (i < size)
			ft_printf("%02hhx", line[i]);
		else
			ft_printf("  ");
		i++;
		if (!(i % 2))
			ft_printf(" ");
	}
	return ;
}

static void			print_ascii_string(ssize_t index, char *line, ssize_t size)
{
	ssize_t		end_point;
	ssize_t		i;

	end_point = index + 16;
	i = index;
	while (i < end_point)
	{
		if (i < size)
		{
			if (ft_isprint(line[i]))
				ft_printf("%hhc", line[i]);
			else
				ft_printf(".");
		}
		else
			ft_printf("  ");
		i++;
	}
	return ;
}

static void			print_lines(char *line, ssize_t size)
{
	ssize_t		index;
	size_t		chars_per_line;

	chars_per_line = 16;
	index = 0;
	while (index < size)
	{
		print_hex_string(index, line, size);
		print_ascii_string(index, line, size);
		ft_printf("\n");
		index += chars_per_line;
	}
	return ;
}

int					main(void)
{
	int			fd;
	ssize_t		ret;
	char		line[BINARY_BUFF_SIZE];

	fd = 0;
	while ((ret = read(fd, &line, BINARY_BUFF_SIZE)) > 0)
		print_lines(line, ret);
	print_lines(line, ret);
	ft_printf("END\n");
	return (0);
}
