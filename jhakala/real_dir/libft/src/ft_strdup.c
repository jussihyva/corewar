/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 10:42:53 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/29 13:23:44 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	char	*tmp;
	size_t	n;

	n = ft_strlen(s1);
	if (!(tmp = ft_strnew(n)))
		return (NULL);
	ft_strncpy(tmp, s1, n);
	return (tmp);
}
