/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 07:57:24 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/15 07:44:34 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.h"
#include "op.h"

t_label *new_label(t_champ *champ, char *str)
{
    t_label *label;
    int i, j, k;

    i = skip_whitespace(str, 0);
    j = i;
    k = -1;
    while (str[i] && is_that_char(str[i], LABEL_CHARS) == 1)
        i++;
    i -= j;
    label = (t_label*)malloc(sizeof(t_label));
    label->place = champ->size;
    label->name = (char*)malloc(sizeof(char) * (i + 1));
    while (++k < i)
        label->name[k] = str[j + k];
    label->name[k] = '\0';
	//testing
    printf("LABEL NAME = %s, ", label->name);
    printf("LABEL PLACE = %d\n", label->place);
    return (label);
}

t_arg   *new_arg(char *line, int *i, int j, int k)
{
    int len, m;
    t_arg *arg;

    arg = (t_arg*)malloc(sizeof(t_arg));
    arg->next = NULL;
    len = arg_size(line, &(*i));
    arg->str = (char*)malloc(sizeof(char) * (len + 1));
    m = -1;
    while (++m < len)
        arg->str[m] = line[*i - len + m];
	*i = skip_whitespace(line, *i);
    arg->str[m] = '\0';
	arg->type = 0;
	arg->label = 0;
	arg->value = 0;
	parse_arg_type(arg);
	possible_arg(arg, j, k);
    return (arg);
}

t_cmd *new_cmd(t_champ *champ, char *line)
{
	t_cmd *cmd;
	int j, i;
	
	cmd = (t_cmd*)malloc(sizeof(t_cmd));
	cmd->next = NULL;
	cmd->arg = NULL;
	cmd->size = 0;
	if ((j = is_label(line)) > 0)
	{
		add_label(&champ->labels, new_label(champ, line));
		j = skip_whitespace(line, j + 1);
		i = parse_cmd(cmd, line, j);
		champ->size += i;
	}
	else
	{
		j = skip_whitespace(line, 0);
		i = parse_cmd(cmd, line, j);
		champ->size += i;
	}
	return (cmd);
}
