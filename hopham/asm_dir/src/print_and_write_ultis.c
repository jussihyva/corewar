/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_and_write_ultis.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/28 12:19:48 by hopham            #+#    #+#             */
/*   Updated: 2020/07/28 12:44:17 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	prio(int *op)
{
	int	i;

	i = 0;
	while (i < 26)
		ft_printf("%d", op[i++]);
	ft_printf("\n");
}

void	pril(t_label *label)
{
	while (label)
	{
		ft_printf("'%s'\n", label->name);
		label = label->next;
	}
}

void	pri(t_cmd *cmd)
{
	t_arg	*arg;
	int		i;

	while (cmd)
	{
		arg = cmd->arg;
		i = 0;
		while (i < cmd->n_arg)
		{
			ft_printf("'%s'", arg->str);
			arg = arg->next;
			i++;
		}
		cmd = cmd->next;
		ft_printf("\n");
	}
}

void	helping(int fd, t_arg *arg, t_cmd *cmd, t_champ *champ)
{
	if (arg->type == 1)
		write_byte(fd, arg->value, 1);
	else if (arg->type == 2)
		write_dir(fd, arg, cmd->dir_size, champ);
	else if (arg->type == 3)
		write_dir(fd, arg, IND_SIZE, champ);
}
