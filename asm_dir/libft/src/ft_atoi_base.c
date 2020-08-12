/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:40:34 by jhakala           #+#    #+#             */
/*   Updated: 2019/12/04 19:32:57 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_whitespace(const char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f')
		return (1);
	return (0);
}

static int	ft_base(int c, int base)
{
	char	*str;
	char	*str2;
	int		i;

	str2 = "0123456789ABCDEF";
	str = "0123456789abcdef";
	i = 0;
	while (i < base)
	{
		if (c == str[i] || c == str2[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int			ft_atoi_base(const char *str, int str_base)
{
	int i;
	int minus;
	int res;

	i = 0;
	minus = 1;
	res = 0;
	while (ft_whitespace(str[i]))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_base(str[i], str_base))
		res = res * str_base + ft_value(str[i++]);
	return (res * minus);
}
