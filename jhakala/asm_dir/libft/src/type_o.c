/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:04:46 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/24 18:12:20 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_padding_o(t_flags *flags, int size)
{
	int width;

	width = 0;
	if (flags->width <= 0)
		return (size);
	while (width++ < flags->width - size)
		ft_write((flags->zero) ? "0" : " ", 1, flags);
	return (size + width - 1);
}

static int		ft_display_o(t_flags *flags, int size, int p, unsigned long
				long int n)
{
	int width_size;
	int width;

	width = 0;
	width_size = 0;
	if (!flags->minus)
	{
		flags->width += (flags->hastag && n == 0) ? 1 : 0;
		flags->hastag ? flags->width-- : 0;
		if (flags->width && flags->zero && flags->space)
			ft_write(" ", 1, flags);
		width_size = ft_padding_o(flags, size) - size;
	}
	if (flags->hastag)
		ft_write("0", 1, flags);
	while (width++ < p)
		ft_write("0", 1, flags);
	if (size > 0 && (flags->hastag && n == 0))
		size -= 1;
	if (size > 0)
		ft_putnbr_base(n, "01234567", 8, flags);
	return (size + width_size);
}

int				type_o(va_list ap, t_flags *flags)
{
	int						size;
	int						precision;
	unsigned long long int	n;

	if (flags->precision != -1)
		flags->zero = 0;
	n = ft_get_n_u(ap, flags);
	size = 0;
	ft_get_n_size_u(n, 8, &size);
	precision = flags->precision - size;
	size = (flags->precision > size) ? flags->precision : size;
	size = (flags->precision == 0 && n == 0) ? 0 : size;
	size += (flags->space);
	precision += (flags->hastag && flags->precision > 0) ? -1 : 0;
	size += (flags->hastag && flags->precision > 0) ? -1 : 0;
	size = ft_display_o(flags, size, precision, n);
	size += (flags->hastag) ? 1 : 0;
	size = (flags->minus) ? ft_padding_o(flags, size) : size;
	return (size);
}
