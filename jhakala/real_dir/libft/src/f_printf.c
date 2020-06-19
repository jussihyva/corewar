/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 21:38:47 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/10 15:03:45 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static t_flags	*ft_init(t_flags *flags)
{
	if (!(flags = (t_flags *)ft_memalloc(sizeof(t_flags))))
		exit(0);
	flags->p = 0;
	flags->p_total = 0;
	return (flags);
}

int				ft_printf(const char *str, ...)
{
	t_flags	*flags;
	va_list	ap;
	int		p;
	char	*str1;

	flags = NULL;
	flags = ft_init(flags);
	p = 0;
	va_start(ap, str);
	str1 = (char*)str;
	while (*str1)
	{
		if (*str1 == '%')
		{
			str1++;
			p += parse(&str1, ap, flags);
		}
		else
			p += ft_write_until(&str1, flags);
	}
	va_end(ap);
	if (flags->p > 0)
		write(1, flags->buffer, (size_t)flags->p);
	free(flags);
	return (p);
}
