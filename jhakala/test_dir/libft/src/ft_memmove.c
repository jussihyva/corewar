/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:33:19 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/30 18:25:13 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*sr;

	i = 0;
	dest = (unsigned char *)dst;
	sr = (unsigned char *)src;
	if (dest == sr)
		return (dst);
	if (sr > dest)
	{
		while (i < len)
		{
			dest[i] = sr[i];
			i++;
		}
	}
	else
	{
		while (len--)
			dest[len] = sr[len];
	}
	return (dst);
}
