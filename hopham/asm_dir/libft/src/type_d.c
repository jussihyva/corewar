/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 01:11:56 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 14:59:29 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_display_sign(long long n, t_flags *flags)
{
	if (n < 0)
		ft_write("-", 1, flags);
	if (flags->plus && n >= 0)
		ft_write("+", 1, flags);
	else if (flags->space && n >= 0)
		ft_write(" ", 1, flags);
}

static int		ft_display_d(t_flags *flags, int size, int precision, long long
				int n)
{
	int width_size;
	int width;

	width = 0;
	width_size = 0;
	if (!flags->minus)
	{
		if (flags->width && flags->zero && flags->precision == -1)
			ft_display_sign(n, flags);
		width_size = ft_padding(flags, size) - size;
		if (flags->width && flags->zero && flags->precision != -1)
			ft_display_sign(n, flags);
	}
	if ((flags->width && (flags->minus || !flags->zero)) || !flags->width)
		ft_display_sign(n, flags);
	while (width++ < precision)
		ft_write("0", 1, flags);
	if (size > 0 && (flags->precision != 0 || !flags->plus))
		ft_putnbr_base((unsigned long long int)(n < 0 ? -n : n),
					"0123456789", 10, flags);
	return (size + width_size);
}

int				type_d(va_list ap, t_flags *flags)
{
	int				size;
	int				precision;
	long long int	n;

	(flags->star_minus == 1) ? flags->precision *= -1 : 0;
	if (flags->precision != -1 && !flags->width)
		flags->zero = 0;
	n = ft_get_n(ap, flags);
	size = 0;
	ft_get_n_size_u((unsigned long long int)(n < 0 ? -n : n), 10, &size);
	precision = flags->precision - size;
	size = (flags->precision > size) ? flags->precision : size;
	size = (flags->precision == 0 && n == 0) ? 0 : size;
	size += (n >= 0 && (flags->plus || flags->space));
	if (n < 0)
		size += 1;
	size = ft_display_d(flags, size, precision, n);
	size = (flags->minus) ? ft_padding(flags, size) : size;
	return (size);
}
