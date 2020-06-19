/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 00:19:46 by jhakala           #+#    #+#             */
/*   Updated: 2019/12/19 15:56:45 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		type_c(va_list ap, t_flags *flags)
{
	int c;
	int width;

	c = va_arg(ap, int);
	width = 0;
	if (flags->width)
	{
		if (flags->minus)
			ft_write(&c, 1, flags);
		while (width++ < flags->width - 1)
			ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	}
	if (!flags->width || !flags->minus)
		ft_write(&c, 1, flags);
	return ((flags->width) ? width : 1);
}
