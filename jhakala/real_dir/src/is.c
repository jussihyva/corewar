/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 01:08:26 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 17:13:22 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		is_that_char(char c, char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (1);
	return (0);
}

int		is_comment(char *str, int i)
{
	i = skip_whitespace(str, i);
	if (str[i] == COMMENT_CHAR)
		return (1);
	return (0);
}

int		is_empty(char *str, int i)
{
	i = skip_whitespace(str, i);
	if (str[i] == '\n' || str[i] == '\0')
		return (1);
	return (0);
}

int		is_label(char *str)
{
	int i;

	i = skip_whitespace(str, 0);
	while (str[i] && is_that_char(str[i], LABEL_CHARS) == 1)
		i++;
	if (str[i] == LABEL_CHAR)
		return (i + 1);
	return (0);
}
