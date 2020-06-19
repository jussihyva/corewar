/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:05:25 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/08 10:19:57 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_x(va_list ap, t_flags *flags)
{
	return (ft_pad_n(ap, flags, "0123456789abcdef", "0x"));
}

int	type_xx(va_list ap, t_flags *flags)
{
	return (ft_pad_n(ap, flags, "0123456789ABCDEF", "0X"));
}

int	type_u(va_list ap, t_flags *flags)
{
	if (flags->hastag)
		return (0);
	return (ft_pad_n(ap, flags, "0123456789", NULL));
}

int	type_p(va_list ap, t_flags *flags)
{
	flags->length_type = 3;
	flags->hastag = 1;
	return (type_x(ap, flags));
}
