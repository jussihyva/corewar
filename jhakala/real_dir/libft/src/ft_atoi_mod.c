/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_mod.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:30:07 by jhakala           #+#    #+#             */
/*   Updated: 2020/02/16 20:56:44 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_error(char *str)
{
	ft_putstr_fd(str, 2);
	return (0);
}

long long int	ft_atoi_mod(const char *str)
{
	size_t	res;
	int		minus;

	minus = 1;
	res = 0;
	while ((*str > 8 && *str < 14) || *str == 32)
		str++;
	if (*str == '-')
		minus = -1;
	if ((*str == '+' || *str == '-') && (*str + 1 > 47 || *str + 1 < 58))
		str++;
	while (*str > 47 && *str < 58)
	{
		res = res * 10 + (*str - 48);
		str++;
	}
	if ((*str > 57 || *str < 48) && *str != '\0')
		return (ft_error("Error: ft_atoi_mod\n"));
	if (res > 9223372036854775807)
		return (ft_error("Error: ft_atoi_mod\n"));
	return (res * minus);
}
