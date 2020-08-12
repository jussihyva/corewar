/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:01:27 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/29 11:04:33 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	const char	*str;
	const char	*find;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	while (*haystack)
	{
		str = haystack;
		find = needle;
		while (*find && *str == *find)
		{
			find++;
			str++;
		}
		if (!(*find))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
