/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:06:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/08 06:03:32 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_precision(char **str, t_flags *flags, va_list ap)
{
	int	precision;

	if (**str == '.')
	{
		*str += 1;
		(!ft_isdigit(**str) && **str != '*') ? flags->precision = 0 : 0;
		if (!ft_isdigit(**str) && **str != '*')
			return (1);
		precision = (**str == '*') ? va_arg(ap, int) : ft_atoi(*str);
		flags->precision = precision;
		(precision < 0 && flags->precision != -1) ? flags->precision *= -1 : 0;
		(**str == '*' && precision < 0) ? flags->star_minus = 1 : 0;
		if (**str == '*' && precision < 0)
			precision = 1;
		else if (precision == 0)
		{
			*str += 1;
			flags->precision = ft_atoi(*str);
		}
		*str += (**str == '0') ? 1 : 0;
		while (precision > 0 && (*str = *str + 1))
			precision /= 10;
		return (1);
	}
	return (0);
}

int		ft_width(char **str, t_flags *flags, va_list ap)
{
	int	width;

	if ((width = ft_atoi(*str)) > 0 || **str == '*')
	{
		if (**str == '*')
		{
			width = va_arg(ap, int);
			if (width < 0)
				flags->minus = 1;
			flags->width = (width < 0 ? width * -1 : width);
			width = 1;
		}
		else
			flags->width = width;
		while (width > 0 && (*str += 1))
			width /= 10;
		return (1);
	}
	return (0);
}

int		ft_flags(char **str, t_flags *flags)
{
	if (*(*str) == '-')
		flags->minus = 1;
	else if (*(*str) == '+')
		flags->plus = 1;
	else if (*(*str) == ' ')
		flags->space = 1;
	else if (*(*str) == '0')
		flags->zero = 1;
	else if (*(*str) == '#')
		flags->hastag = 1;
	else
		return (0);
	(*str)++;
	return (1);
}

int		ft_length(char **str, t_flags *flags)
{
	int i;

	i = 0;
	(**str == 'h') ? h_length(str, flags) : i++;
	(**str == 'l') ? l_length(str, flags) : i++;
	(**str == 'L') ? bigl_length(str, flags) : i++;
	if (i == 3)
		return (0);
	return (1);
}
