/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:09:44 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/30 19:16:58 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_itoa(int n)
{
	char	*str;
	int		n_len;
	int		neg;
	long	tmp;

	neg = 0;
	tmp = n;
	if (n < 0)
	{
		tmp *= -1;
		neg = 1;
	}
	n_len = ft_countdigit(n);
	if (!(str = ft_strnew(n_len + neg)))
		return (NULL);
	str[n_len + neg] = '\0';
	while (n_len)
	{
		n_len--;
		str[n_len + neg] = (tmp % 10) + '0';
		tmp = tmp / 10;
	}
	if (neg == 1)
		str[0] = '-';
	return (str);
}
