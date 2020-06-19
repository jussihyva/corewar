/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:26:35 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/29 11:31:29 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*des;
	unsigned char	*sr;

	des = (unsigned char *)dest;
	sr = (unsigned char *)src;
	if (src == dest || !n)
		return (dest);
	i = 0;
	while (i < n)
	{
		des[i] = sr[i];
		i++;
	}
	return (dest);
}
