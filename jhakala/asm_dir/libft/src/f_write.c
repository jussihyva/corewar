/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:51:46 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/07 01:22:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_write_char(char c, t_flags *flags)
{
	return (ft_write(&c, 1, flags));
}

int		ft_write(void *s, int size, t_flags *flags)
{
	char	*str;
	int		i;

	if (flags->p + size > 1024)
	{
		write(1, flags->buffer, (size_t)flags->p);
		flags->p = 0;
		if (size > 1024)
		{
			write(1, s, (size_t)size);
			return (size);
		}
	}
	i = 0;
	str = s;
	while (i < size)
		flags->buffer[flags->p++] = str[i++];
	flags->p_total += size;
	return (size);
}

int		ft_write_until(char **format, t_flags *flags)
{
	int next;

	if (ft_strchr(*format, '%'))
		next = (int)(ft_strchr(*format, '%') - *format);
	else
		next = (int)ft_strlen(*format);
	ft_write(*format, next, flags);
	*format += next;
	return (next);
}
