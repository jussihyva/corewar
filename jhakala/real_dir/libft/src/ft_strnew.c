/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 17:19:35 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/18 17:40:01 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char *mem;

	if (!(mem = ft_memalloc(size + 1)))
		return (NULL);
	while (*mem)
	{
		*mem = '\0';
		mem++;
	}
	*mem = '\0';
	return (mem);
}
