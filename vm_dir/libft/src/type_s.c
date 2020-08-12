/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_s.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:49:05 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/08 06:03:55 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_s(va_list ap, t_flags *flags)
{
	char	*str;
	int		width;
	int		size;

	str = va_arg(ap, char*);
	if (!str)
		size = 6;
	else
		size = (int)ft_strlen(str);
	size = (flags->precision == 0) ? 0 : size;
	if (flags->precision > 0 && flags->precision < size && size > 0)
		size = size - (size - flags->precision);
	if (flags->width)
	{
		if (flags->minus)
			ft_write((str) ? str : "(null)", size, flags);
		width = 0;
		while (width++ < flags->width - size)
			ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	}
	if (!flags->width || !flags->minus)
		ft_write((str) ? str : "(null)", size, flags);
	return (size + (flags->width - size > 0 ? flags->width - size : 0));
}
