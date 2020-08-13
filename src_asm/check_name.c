/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_name.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 09:28:42 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/13 18:41:08 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_name_error(char *str)
{
	ft_printf("Invalid file end: '%s'\n", str);
	return (0);
}

void	free_tmp_name(char *name, char *tmp)
{
	free(name);
	free(tmp);
}

char	*ft_name(char *tmp, char *end, char *name)
{
	name = ft_strjoin(tmp, end);
	ft_printf("Writing to file :\"%s\"\n", name);
	return (name);
}

int		check_name(int *fd, char *str, int *op, char *end)
{
	int		i;
	int		j;
	char	*tmp;
	char	*name;

	name = NULL;
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
		*fd = open(
		name = ft_name(tmp, end, name), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		free_tmp_name(name, tmp);
		return (*fd > 0 ? 1 : 0);
	}
	return (ft_name_error(str));
}
