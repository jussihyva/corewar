/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:28:31 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 19:32:13 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

int		calc_cmd_size(t_cmd *cmd)
{
	int		size;
	int		i;
	t_arg	*arg;

	i = -1;
	size = 1;
	if (cmd->statement_code == 1)
		size += 1;
	arg = cmd->arg;
	while (++i < cmd->n_arg)
	{
		if (arg->type == 1)
			size += 1;
		else if (arg->type == 2)
			size += cmd->dir_size;
		else if (arg->type == 3)
			size += 2;
		arg = arg->next;
	}
	cmd->size = size;
	return (size);
}

int		arg_str_size(char *str, int *i)
{
	int len;

	len = 0;
	if (str[*i] == SEPARATOR_CHAR)
		(*i)++;
	*i = skip_whitespace(str, *i);
	while (str[*i] != ' ' && str[*i] != '	' && str[*i] != SEPARATOR_CHAR &&
		str[*i] != '\n' && str[*i] && str[*i] != COMMENT_CHAR[0] &&
		str[*i] != COMMENT_CHAR[1])
	{
		len++;
		(*i)++;
	}
	return (len);
}

int		arg_reg(t_arg *arg, char *str, int i)
{
	int res;

	res = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (str[i] != '\0' || res > REG_NUMBER)
		arg->error = ARG_ERROR_2;
	return (res);
}

int		arg_dir(t_arg *arg, char *str, int i)
{
	int res;
	int minus;

	minus = 1;
	res = 0;
	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (str[i] != '\0')
		arg->error = ARG_ERROR_3;
	return (res * minus);
}

char	*arg_dir_label(t_arg *arg, char *str, int i)
{
	char	*res;
	int		j;

	j = 0;
	res = (char*)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	if (str[i] != '\0')
		arg->error = ARG_ERROR_4;
	return (res);
}
