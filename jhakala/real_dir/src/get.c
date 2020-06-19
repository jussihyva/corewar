/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:21:50 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 02:24:32 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		count(char *line)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '"')
			count++;
		i++;
	}
	return (count);
}

char	*copy_to(char *str, int i, int j)
{
	char *res;
	int k;

	k = 0;
	res = ft_strnew(j - i);
	while (k + i < j)
	{
		res[k] = str[k + i];
		k++;
	}
	free(str);
	return (res);
}

char	*append_to_str(int fd)
{
	char	*str;
	char	*tmp;
	char	*line;

	line = NULL;
	get_next_line(fd, &line);
	str = ft_strdup(line);
	while (count(str) == 1)
	{
		free(line);
		tmp = str;
		if (get_next_line(fd, &line) > 0)
			str = ft_strnjoin(tmp, line);
		else
			str = ft_strjoin(tmp, line);
		free(tmp);
	}
	free(line);
	return (str);
}

char	*get_str(int fd, char *s1)
{
	char	*str;
	int		i;
	int		j;

	str = append_to_str(fd);
	i = skip_whitespace(str, 0);
	j = 0;
	while (str[i + j] == s1[j] && str[i + j] && s1[j])
		j++;
	if (s1[j] != '\0')
		return (NULL);
	i = skip_whitespace(str, i + j);
	j = skip_to(str, '"', i + 1);
	return (copy_to(str, i + 1, j));
}
