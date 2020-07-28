/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 15:17:54 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/28 12:10:48 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		possible_arg(t_arg *arg, int j, int k)
{
	int i;

	i = g_op_tab[j].t_arg[k];
	if (arg->type == 1 && (i == 1 || i == 3 || i == 5 || i == 7))
		return (1);
	else if (arg->type == 2 && (i == 2 || i == 3 || i == 6 || i == 7))
		return (1);
	else if (arg->type == 3 && (i == 4 || i == 5 || i == 6 || i == 7))
		return (1);
    return (0);
}

int		parse_arg_type(t_arg *arg)
{
	int res;
	
	res = 3;
	if (arg->str[0] == 'r')
	{
		res = 1;
		arg->value = arg_reg(arg, arg->str, 1);
	}
	else if (arg->str[0] == DIRECT_CHAR) 
	{
		res = 2;
		if (arg->str[1] != LABEL_CHAR)
			arg->value = arg_dir(arg, arg->str, 1);
		if (arg->str[1] == LABEL_CHAR)
			arg->label = arg_dir_label(arg, arg->str, 2);
	}
	else if (arg->str[0] == '-' || (arg->str[0] >= '0' && arg->str[0] <= '9'))
		arg->value = arg_dir(arg, arg->str, 0);
	else if (arg->str[0] == LABEL_CHAR)
		arg->label = arg_dir_label(arg, arg->str, 1);
	else
		return (0);
	return (res);
}

t_arg	*new_arg(char *line, int *i, int j, int k)
{
	t_arg	*arg;
	int		len;

	if (!(arg = (t_arg*)malloc(sizeof(t_arg))))
		return (NULL);
	arg->next = NULL;
	len = arg_str_size(line, &(*i));
	arg->str = ft_strsub(line, *i - len, len);
	arg->type = 0;
	arg->label = 0;
	arg->value = 0;
	arg->error = 0;
	arg->type = parse_arg_type(arg);
	if (k < g_op_tab[j].n_arg - 1)
	{
		*i = skip_whitespace(line, *i);
		if (line[*i] != SEPARATOR_CHAR)
			arg->error = ARG_ERROR_5;
	}
	else if (valid_end(line, *i) == 0)
		arg->error = ARG_ERROR_5;
	if (possible_arg(arg, j, k) == 0)
		arg->error = ARG_ERROR_1;
	return (arg);
}	

int		parse_cmd_to_args(t_cmd *cmd, char *line, int i, int j)
{
	int k;

	k = -1;
	i += g_op_tab[j].size;
	cmd->n_arg = g_op_tab[j].n_arg;
	cmd->op_code = g_op_tab[j].op_code;
	cmd->statement_code = g_op_tab[j].statement_code;
	cmd->dir_size = g_op_tab[j].dir_size;
	while (++k < cmd->n_arg)
		add_arg(&cmd->arg, new_arg(line, &i, j, k));
	cmd->error = rev_arg(&cmd->arg);
	return (calc_cmd_size(cmd));
}

int		parse_cmd(t_cmd *cmd, char *line, int i)
{
	char	*word;
	int		j;

	word = ft_strsub(line, i, 5);
	j = 0;
	while (j < 16)
	{
		if (ft_strncmp(word, g_op_tab[j].str, g_op_tab[j].size) == 0)
		{
			free(word);
			return (parse_cmd_to_args(cmd, line, i, j));
		}
		j++;
	}
	if (j == 16)
		cmd->error = 7;
	free(word);
	return (0);
}
