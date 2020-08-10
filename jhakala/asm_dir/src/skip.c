/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 01:08:26 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 15:53:53 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		skip_whitespace(char *str, int i)
{
	while (str[i] && (str[i] == ' ' || str[i] == '	'))
		i++;
	return (i);
}

int		skip_to(char *str, char c, int i)
{
	int j;

	if (i < 0 || str[i++] != '"')
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] != c)
		return (-1);
	j = i;
	if (str[j] == '"')
		j++;
	while (str[j])
	{
		if (ft_strchr(COMMENT_CHAR, str[i]) || str[j] == '\n') // str[j] == COMMENT_CHAR
			break ;
		if (str[j] != ' ' && str[j] != '	')
			return (-1);
		j++;
	}
	return (i);
}

int		valid_end(char *str, int i)
{
	i = skip_whitespace(str, i);
	if (ft_strchr(COMMENT_CHAR, str[i]) || str[i] == '\0' || str[i] == '\n') // str[i] == COMMENT_CHAR
		return (1);
	return (0);
}
