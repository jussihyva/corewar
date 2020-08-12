/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 10:59:35 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/10 18:51:57 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

void	write_byte(int fd, int str, int len)
{
	unsigned char	content[len];
	int				i;

	i = len - 1;
	while (i > -1)
	{
		content[i--] = (unsigned char)str;
		str >>= 8;
	}
	i = 0;
	while (i < len)
		write(fd, &content[i++], 1);
}

void	write_header(t_champ *champ, int fd)
{
	int len;
	int i;

	write_byte(fd, COREWAR_EXEC_MAGIC, 4);
	len = strlen(champ->name);
	i = 0;
	while (i < len)
		write_byte(fd, champ->name[i++], 1);
	while (i++ < PROG_NAME_LENGTH)
		write_byte(fd, 0, 1);
	i = 0;
	while (i++ < 4)
		write_byte(fd, 0, 1);
	write_byte(fd, champ->size, 4);
	len = strlen(champ->comment);
	i = 0;
	while (i < len)
		write_byte(fd, champ->comment[i++], 1);
	while (i++ < COMMENT_LENGTH)
		write_byte(fd, 0, 1);
	i = 0;
	while (i++ < 4)
		write_byte(fd, 0, 1);
}

void	write_dir(int fd, t_arg *arg, int i, t_champ *champ)
{
	t_label *label;

	label = champ->label;
	if (!arg->label)
		write_byte(fd, arg->value, i);
	else
	{
		while (label)
		{
			if (strcmp(label->name, arg->label) == 0)
				break ;
			label = label->next;
		}
		write_byte(fd, label->place - champ->size, i);
	}
}

void	write_statement_code(t_arg *arg, int fd, int check)
{
	int statement_code;
	int i;

	statement_code = 0;
	i = 3;
	if (check == 1)
	{
		while (i > 0)
		{
			if (arg)
			{
				statement_code += arg->type << (i * 2);
				arg = arg->next;
			}
			i--;
		}
		write_byte(fd, statement_code, 1);
	}
}

void	write_to_file(t_champ *champ, int fd)
{
	t_cmd *cmd;
	t_arg *arg;

	write_header(champ, fd);
	champ->size = 0;
	cmd = champ->cmd;
	while (cmd)
	{
		if (cmd->op_code > 0 && cmd->op_code < 17)
		{
			write_byte(fd, cmd->op_code, 1);
			write_statement_code(cmd->arg, fd, cmd->statement_code);
			arg = cmd->arg;
			while (arg)
			{
				arg->type == 1 ? write_byte(fd, arg->value, 1) : 0;
				arg->type == 2 ? write_dir(fd, arg, cmd->dir_size, champ) : 0;
				arg->type == 3 ? write_dir(fd, arg, IND_SIZE, champ) : 0;
				arg = arg->next;
			}
			champ->size += cmd->size;
		}
		cmd = cmd->next;
	}
}
