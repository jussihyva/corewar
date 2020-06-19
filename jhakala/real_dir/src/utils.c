/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 01:08:26 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 01:27:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		skip_whitespace(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	return (i);
}

int		skip_to(char *str, char c, int i)
{
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (0);
	return (i);
}
