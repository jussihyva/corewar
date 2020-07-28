/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_f.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 19:37:59 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 15:07:55 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int			f_padding(char to_print, int padding, t_flags *flags)
{
	int i;

	i = 0;
	while (padding > 0)
	{
		ft_write_char(to_print, flags);
		i++;
		padding--;
	}
	return (i);
}

static int			f_width(int f_len, char *p, t_flags *flags, int negative)
{
	int len;

	*p = (flags->zero && (flags->precision == 6 && !flags->minus)) ? '0' : ' ';
	len = f_len + ((negative || flags->space || flags->plus) ? 1 : 0);
	return ((flags->width > len) ? flags->width - len : 0);
}

static int			f_len(long double n, t_flags *flags)
{
	int					len;
	unsigned long long	whole;

	len = 0;
	n = (n < 0) ? -n : n;
	whole = (unsigned long long)n;
	len += (whole == 0) ? 1 : 0;
	while (whole > 0)
	{
		len++;
		whole /= 10;
	}
	len += (flags->precision != 0) ? flags->precision + 1 : 0;
	len += (flags->hastag && flags->precision == 0) ? 1 : 0;
	return (len);
}

static long double	f_get(va_list ap, t_flags *flags)
{
	long double n;

	if (flags->length_type == 5)
		n = va_arg(ap, long double);
	else
	{
		n = va_arg(ap, double);
		return ((double)n);
	}
	return (n);
}

int					type_f(va_list ap, t_flags *flags)
{
	int			size;
	int			padding;
	long double	n;
	char		to_print;

	size = 0;
	n = f_get(ap, flags);
	if (flags->precision == -1)
		flags->precision = 6;
	size += f_len(n, flags);
	padding = f_width(size, &to_print, flags, n < 0);
	if (!flags->minus && !flags->zero)
		size += f_padding(to_print, padding, flags);
	if (n >= 0 && flags->space && !flags->plus)
	{
		ft_putchar(' ');
		size++;
	}
	size += f_putsign(n, flags);
	if (!flags->minus && flags->zero)
		size += f_padding(to_print, padding, flags);
	ft_writef(n, flags);
	if (flags->minus)
		size += f_padding(to_print, padding, flags);
	return (size);
}
