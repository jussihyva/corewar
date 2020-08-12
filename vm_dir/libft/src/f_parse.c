/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 21:48:25 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 15:06:10 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		flag_reset(t_flags *flags)
{
	flags->precision = -1;
	flags->minus = 0;
	flags->plus = 0;
	flags->space = 0;
	flags->zero = 0;
	flags->width = 0;
	flags->length_type = 0;
	flags->hastag = 0;
	flags->star_minus = 0;
}

static t_type	g_type[21] = {
	{'c', type_c}, {'d', type_d}, {'s', type_s}, {'o', type_o}, {'x', type_x},
	{'X', type_xx}, {'p', type_p}, {'i', type_d}, {'u', type_u}, {'f', type_f}
};

int				ft_padding(t_flags *flags, int size)
{
	int		width;
	int		count;

	count = flags->width - size;
	count = (flags->precision == -1) ? 0 : count;
	count = (flags->star_minus) ? -2147483648 : count;
	width = 0;
	if (flags->width <= 0)
		return (size);
	while (width++ < flags->width - size)
	{
		if (flags->zero && !flags->minus && flags->width > size + count++)
			ft_write("0", 1, flags);
		else
			ft_write(" ", 1, flags);
	}
	return (size + width - 1);
}

static int		ft_type(char **str, va_list ap, t_flags *flags)
{
	int ac;
	int size;

	ac = 0;
	while (ac < 21)
	{
		if (**str == g_type[ac].name)
		{
			*str += 1;
			flags->type = g_type[ac].name;
			return (g_type[ac].f(ap, flags));
		}
		ac++;
	}
	size = 1;
	if (!flags->minus)
		size = ft_padding(flags, size);
	ft_write(*str, 1, flags);
	if (flags->minus)
		size = ft_padding(flags, size);
	*str += 1;
	return (size);
}

int				parse(char **str, va_list ap, t_flags *flags)
{
	int flags_found;

	while (**str)
	{
		flags_found = 0;
		flag_reset(flags);
		while (ft_length(str, flags) || ft_flags(str, flags) ||
			ft_width(str, flags, ap) || ft_precision(str, flags, ap))
			flags_found = 1;
		if (ft_isalpha(**str) || **str == '%')
			return (ft_type(str, ap, flags));
		else if (!*(*str + 1) || !flags_found)
			return (0);
	}
	return (0);
}
