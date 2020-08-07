/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_head.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:21:50 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/28 12:13:01 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		comment_line(char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ' && line[i] == '	')
		i++;
	if (line[i] == COMMENT_CHAR)
	{
		free(line);
		return (1);
	}
	return (0);
}

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
	char	*res;
	int		k;

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

char	*append_to_str(int fd, int *r)
{
	char	*str;
	char	*tmp;
	char	*line;
	int		i;

	if ((i = get_next_line(fd, &line)) < 1)
		return (NULL);
	while (comment_line(line) > 0)
		i = get_next_line(fd, &line);
	str = ft_strdup(line);
	while (i > 0 && count(str) == 1)
	{
		free(line);
		tmp = str;
		if ((i = get_next_line(fd, &line)) > 0)
			str = ft_strnjoin(tmp, line);
		else
			str = ft_strjoin(tmp, line);
		free(tmp);
		(*r)++;
	}
	free(line);
	if ((i = count(str)) != 2)
		free(str);
	return (i == 2 ? str : NULL);
}

char	*get_str(int fd, char *s1, int *r)
{
	char	*str;
	int		i;
	int		j;

	if (!(str = append_to_str(fd, &(*r))))
		return (NULL);
	i = skip_whitespace(str, 0);
	j = 0;
	while (str[i + j] == s1[j] && str[i + j] && s1[j])
		j++;
	if (s1[j] != '\0')
	{
		free(str);
		return (NULL);
	}
	i = skip_whitespace(str, i + j);
	if ((j = skip_to(str, '"', i)) == -1)
	{
		free(str);
		return (NULL);
	}
	return (copy_to(str, i + 1, j));
}