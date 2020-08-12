/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:48:59 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 14:52:41 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_hastag(unsigned long long int n, t_flags *flags, int *size,
				char *content)
{
	int precision;

	precision = 0;
	if (n == 0 && flags->type != 'p')
		flags->hastag = 0;
	if (flags->hastag && (!flags->width || flags->minus || flags->zero ||
						(precision = flags->precision > *size)))
		ft_write(content, (int)ft_strlen(content), flags);
	if (flags->hastag && (flags->width && !precision) && flags->type != 'p')
		*size += (int)ft_strlen(content);
	return (precision);
}

void	ft_display_padding(t_flags *flags, unsigned long long int n, int *size,
				char *base)
{
	int width;
	int precision;

	if (flags->precision <= 0 && flags->width <= 0)
	{
		(flags->type == 'p' && *size > 0) ? *size += 2 : 0;
		return ;
	}
	width = 0;
	precision = flags->precision - *size;
	*size = (flags->precision > *size) ? flags->precision : *size;
	while (flags->minus && width++ < precision)
		ft_write("0", 1, flags);
	if (flags->minus && flags->precision != -1 && (flags->precision || n != 0))
		ft_putnbr_base(n, base, ft_strlen(base), flags);
	width = ((flags->type == 'x' || flags->type == 'X') &&
			flags->hastag && flags->minus) ? -2 : 0;
	while (width++ < flags->width - (*size + (flags->type == 'p' ? 2 : 0)))
		ft_write((flags->zero && !flags->minus) ? "0" : " ", 1, flags);
	width = 0;
	while (!flags->minus && width++ < precision)
		ft_write("0", 1, flags);
	(*size > 0 && flags->type == 'p') ? *size += 2 : 0;
	*size -= (flags->hastag && (flags->type == 'x' || flags->type == 'X') &&
			flags->precision < *size) ? 1 : 0;
}
