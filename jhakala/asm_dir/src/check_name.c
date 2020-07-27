/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 09:28:42 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/27 16:03:32 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_name_error(char* str)
{
	ft_printf("Invalid file end: '%s'\n", str);
	return (0);
}

int		check_name(int *fd, char *str, int *op, char *end)
{
	int i;
	int j;
	char *tmp;
	char *name;
	
	if ((j = ft_strlen(str) - 2) > 0 && str[j] == '.' && str[j + 1] == 's')
	{
		i = op[22] == 1 ? j - 2 : 0;
		while (i > 0)
		{
			if (str[i] == '/')
			{
				i++;
				break ;
			}
			i--;
		}
		ft_strlcat((tmp = ft_strnew(j - i + 5)), &(*(str + i)), j - i + 1);
		*fd = open((name = ft_strjoin(tmp, end)), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_printf("Writing to file :\"%s\"\n", name);
		free(tmp);
		free(name);
		return (*fd > 0 ? 1 : 0);
	}
	return (ft_name_error(str));
}
