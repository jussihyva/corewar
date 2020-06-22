/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_writef.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 20:24:35 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 15:07:18 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			f_putsign(long double n, t_flags *flags)
{
	if (n < 0)
	{
		ft_write_char('-', flags);
		return (1);
	}
	else if (n >= 0 && flags->plus)
	{
		ft_write_char('+', flags);
		return (1);
	}
	return (0);
}

static void	manipulate(t_flags *flags)
{
	int i;
	int count;

	count = 1;
	i = 10;
	flags->buffer[flags->p] = '0';
	while (i == 10)
	{
		if (flags->buffer[flags->p - count] == '.')
			count++;
		flags->buffer[flags->p - count] = flags->buffer[flags->p - count] + 1;
		if (flags->buffer[flags->p - count] == ':')
		{
			flags->buffer[flags->p - count] = '0';
			count++;
		}
		else
			i = 0;
	}
}

static void	ft_writef_last(long double n, t_flags *flags)
{
	int i;

	n *= 10;
	i = (int)n;
	n -= i;
	if (n >= 0.5)
		i++;
	if (i == 10)
	{
		manipulate(flags);
		ft_write_char('0', flags);
	}
	else
		ft_write_char(i + '0', flags);
}

void		ft_writef(long double n, t_flags *flags)
{
	long double			num;
	unsigned long long	whole;

	num = (n < 0) ? -n : n;
	whole = (unsigned long long)num;
	if (num - whole >= 0.5 && flags->precision == 0)
		whole += 1;
	num -= whole;
	ft_putnbr_base(whole, "0123456789", 10, flags);
	num += (flags->precision <= 15) ? 0.0000000000000001 : 0;
	if (flags->precision > 0 || flags->hastag)
		ft_write_char('.', flags);
	if (flags->precision != 0)
	{
		while (flags->precision > 1)
		{
			num *= 10;
			whole = (unsigned long long)num;
			num -= whole;
			whole %= 10;
			ft_write_char(whole + '0', flags);
			flags->precision--;
		}
		ft_writef_last(num, flags);
	}
}
