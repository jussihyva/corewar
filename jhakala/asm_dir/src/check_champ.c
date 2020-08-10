/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 20:25:54 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 18:10:41 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int		ft_error(int i, char *str, char *line)
{
	ft_printf("ERROR: row: %d: '%s', %s\n", i, line, str);
	return (1);
}

int		ft_label_error(int i, char *str, char *label, char *line)
{
	ft_printf("ERROR: row: %d: '%s', %s '%s'\n", i, line, str, label);
	exit(0);
	return (1);
}

int		check_label(char *word, t_label *label)
{
	while (label)
	{
		if (ft_strcmp(word, label->name) == 0)
		{
			return (0);
		}
		label = label->next;
	}
	return (1);
}

int		check_champ(t_champ *champ)
{
	t_cmd	*cmd;
	t_arg	*arg;

	cmd = champ->cmd;
	while (cmd)
	{
		arg = cmd->arg;
//		ft_printf("%d, %d, %d, %d\n", cmd->op_code, cmd->size, cmd->row, cmd->error);
		if (cmd->error != 0)
			return (ft_error(cmd->row, g_error[cmd->error].str, cmd->line));
		while (arg)
		{
			if (arg->error != 0)
				return (ft_error(cmd->row, g_error[arg->error].str, cmd->line));
			if (arg->label != 0)
			{
				if (check_label(arg->label, champ->label) == 1)
					return (ft_label_error(cmd->row, g_error[6].str, arg->label, cmd->line));
			}
			arg = arg->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
	
