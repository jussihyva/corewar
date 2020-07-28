/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 14:36:47 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/28 12:15:04 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"

t_label	*new_label(t_champ *champ, char *line)
{
	t_label	*label;
	int		i;
	int		j;

	i = skip_whitespace(line, 0);
	j = i;
	while (line[i] && is_that_char(line[i], LABEL_CHARS) == 1)
		i++;
	i -= j;
	if (!(label = (t_label*)malloc(sizeof(t_label))))
		return (NULL);
	label->place = champ->size;
	label->name = ft_strsub(line, j, i);
	return (label);
}

void	default_cmd(t_cmd *cmd)
{
	cmd->op_code = 0;
	cmd->statement_code = 0;
	cmd->dir_size = 0;
	cmd->n_arg = 0;
	cmd->size = 0;
	cmd->error = 0;
	cmd->next = NULL;
	cmd->arg = NULL;
}

t_cmd	*new_cmd(t_champ *champ, char *line, int row_n)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	if (!(cmd = (t_cmd*)malloc(sizeof(t_cmd))))
		return (NULL);
	default_cmd(cmd);
	cmd->row = row_n;
	if ((j = is_label(line)) > 0)
		add_label(&champ->label, new_label(champ, line));
	if (line[j] && !is_comment(line, j) && !is_empty(line, j))
	{
		j = skip_whitespace(line, j);
		i = parse_cmd(cmd, line, j);
		champ->size += i;
	}
	return (cmd);
}

int		check_last_line(char *str)
{
	int i;

	i = skip_whitespace(str, 0);
	if (str[i] != '\0')
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

t_cmd	*get_lines(t_champ *champ, int fd, int row_n)
{
	char	*line;
	char	*last_line;
	t_cmd	*cmd;
	int		i;

	cmd = NULL;
	last_line = NULL;
	while ((i = get_next_line(fd, &line)) > 0)
	{
		row_n++;
		if (ft_strlen(line) > 0 && !is_comment(line, 0) && !is_empty(line, 0))
			add_cmd(&cmd, new_cmd(champ, line, row_n));
		if (last_line != NULL)
			free(last_line);
		last_line = line;
	}
	if (check_last_line(last_line) == 0)
		cmd->error = 8;
	if (cmd != NULL)
		rev_cmd(&cmd);
	if (champ->label != NULL)
		rev_label(&champ->label);
	return (cmd);
}
