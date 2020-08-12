/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_bases.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:23:19 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 14:51:52 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long long int			ft_get_n(va_list ap, t_flags *flags)
{
	long long int n;

	n = va_arg(ap, long long int);
	if (flags->length_type == 1)
		n = (char)n;
	else if (flags->length_type == 2)
		n = (short int)n;
	else if (flags->length_type == 3)
		n = (long int)n;
	else if (flags->length_type == 4)
		n = (long long int)n;
	else
		n = (int)n;
	return (n);
}

unsigned long long int	ft_get_n_u(va_list ap, t_flags *flags)
{
	unsigned long long int n;

	n = va_arg(ap, unsigned long long int);
	if (flags->length_type == 1)
		n = (unsigned char)n;
	else if (flags->length_type == 2)
		n = (unsigned short int)n;
	else if (flags->length_type == 3)
		n = (unsigned long int)n;
	else if (flags->length_type == 4)
		n = (unsigned long long int)n;
	else
		n = (unsigned int)n;
	return (n);
}

void					ft_putnbr_base(unsigned long long int n,
			char *str, unsigned long long int length, t_flags *flags)
{
	if (n >= length)
		ft_putnbr_base(n / length, str, length, flags);
	ft_write_char(str[n % length], flags);
}

void					ft_get_n_size_u(unsigned long long int n,
						unsigned long long int length, int *size)
{
	*size += 1;
	while (n >= length)
	{
		n /= length;
		*size += 1;
	}
}

int						ft_pad_n(va_list ap, t_flags *flags,
							char *base, char *content)
{
	int						size;
	int						precision;
	unsigned long long int	n;

	if (flags->precision != -1)
		flags->zero = 0;
	size = 0;
	n = ft_get_n_u(ap, flags);
	ft_get_n_size_u(n, ft_strlen(base), &size);
	precision = ft_hastag(n, flags, &size, content);
	(flags->precision == 0 && n == 0) ? size = 0 : 0;
	(!flags->minus) ? ft_display_padding(flags, n, &size, base) : 0;
	if (flags->hastag && flags->width && !flags->minus &&
		!flags->zero && !precision)
		ft_write(content, (int)ft_strlen(content), flags);
	if (size > 0 && !(flags->precision != -1 && flags->width && flags->minus))
		ft_putnbr_base(n, base, ft_strlen(base), flags);
	if (flags->hastag && size > 0 && ((!flags->width || flags->minus)
							|| precision) && flags->type != 'p')
		size += (int)ft_strlen(content);
	(size == 0 && flags->type == 'p') ? size = 2 : 0;
	(flags->minus) ? ft_display_padding(flags, n, &size, base) : 0;
	return (flags->width - size > 0 ? flags->width : size);
}
