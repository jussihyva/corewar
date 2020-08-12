/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:04:44 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/29 12:48:09 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *hay, const char *need, size_t len)
{
	const char	*str;
	const char	*find;
	size_t		i;

	if (ft_strlen(need) == 0)
		return ((char *)hay);
	while (*hay && len)
	{
		str = hay;
		find = need;
		i = len;
		while (*find && *str == *find && i)
		{
			find++;
			str++;
			i--;
		}
		if (!(*find))
			return ((char *)hay);
		hay++;
		len--;
	}
	return (NULL);
}
