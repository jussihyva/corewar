/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 21:08:03 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/11 08:31:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void				print_hex_string(ssize_t index, char *line, ssize_t size)
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

void				print_hex(char *file_content, ssize_t size)
{
	ssize_t		index;
	size_t		chars_per_line;

	chars_per_line = 16;
	index = 0;
	while (index < size)
	{
		ft_printf("%08x: ", index);
		print_hex_string(index, file_content, size);
		print_ascii_string(index, file_content, size);
		ft_printf("\n");
		index += chars_per_line;
	}
	return ;
}
