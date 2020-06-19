/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:55:10 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/29 11:33:27 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = ft_strlen(dst);
	if (i >= dstsize)
		return (dstsize + ft_strlen(src));
	dst = ft_strncat(dst, src, dstsize - i - 1);
	return (i + ft_strlen(src));
}
