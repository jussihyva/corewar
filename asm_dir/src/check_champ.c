/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_champ.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 20:25:54 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 18:56:19 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		ft_error(int i, char *str, char *line, int *op)
{
	ft_printf("ERROR: row: %d: '%s', %s\n", i, line, str);
	if (op[21] == 0)
	{
		if (op[20] == 1)
			system("leaks asm");
		exit(0);
	}
	return (1);
}

int		ft_label_error(int i, char *str, char *label, char *line)
{
	ft_printf("ERROR: row: %d: '%s', %s '%s'\n", i, line, str, label);
	return (1);
}

int		check_label(char *word, t_label *label)
{
	while (label)
	{
		if (ft_strcmp(word, label->name) == 0)
			return (0);
		label = label->next;
	}
	return (1);
}

int		check_arg(t_champ *champ, t_cmd *cmd, t_arg *arg, int *op)
{
	int check;

	check = 0;
	while (arg)
	{
		if (arg->error != 0)
			check = ft_error(cmd->row, g_error[arg->error].str, cmd->line, op);
		if (arg->label != 0)
		{
			if (check_label(arg->label, champ->label) == 1)
			{
				check = ft_label_error(cmd->row, g_error[6].str, arg->label,
									cmd->line);
				if (op[21] == 0)
				{
					if (op[20] == 1)
						system("leaks asm");
					exit(0);
				}
			}
		}
		arg = arg->next;
	}
	return (0);
}

int		check_champ(t_champ *champ, int *op)
{
	t_cmd	*cmd;
	t_arg	*arg;
	int		check;

	cmd = champ->cmd;
	check = 0;
	while (cmd)
	{
		arg = cmd->arg;
		if (cmd->error != 0)
			check = ft_error(cmd->row, g_error[cmd->error].str, cmd->line, op);
		if (check_arg(champ, cmd, arg, op) == 1)
			check = 1;
		cmd = cmd->next;
	}
	if (check == 1)
		return (1);
	return (0);
}
