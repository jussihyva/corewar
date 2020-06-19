/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:48:03 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/29 18:53:42 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	int i;
	int j;
	int len;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && (s[i] == 32 || s[i] == '\n' || s[i] == '\t'))
		i++;
	j = ft_strlen(s);
	while (i < j && (s[j - 1] == 32 ||
					s[j - 1] == '\n' || s[j - 1] == '\t'))
		j--;
	if (i == j)
		return (ft_strnew(1));
	len = j - i;
	return (ft_strsub(s, i, len));
}
