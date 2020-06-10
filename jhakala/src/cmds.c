/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 19:00:15 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/10 19:27:31 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "op.h"

/* only 0, 1 and 2 are take care of now for seeing if it works like i imagined
** will do this parsing part earlier in future when i have time.
** wrong sizes placeholders 
*/

void	cmd_empty(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 0;
	printf("free line");
	j = skip_whitespace(str, j);
	free(str);
	line->op_code = 0;
}

void	cmd_live(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 5;
	j += 4;
	j = skip_whitespace(str, j);
	line->arg1 = (char*)malloc(sizeof(char) * 4);
	line->arg1[0] = str[j];
	line->arg1[1] = str[j + 1];
	if (str[j + 2] >= '0' && str[j + 2] <= '9')
	{
		line->arg1[2] = str[j + 2];
		line->arg1[3] = '\0';
	}
	else
		line->arg1[2] = '\0';
	line->op_code = 1;
}

void	cmd_ld(t_champ *champ, t_line *line, char *str, int j)
{
	int i = 0, k = -1;
	champ->size += 7;
	j += 2;
	j = skip_whitespace(str, j);
	while (str[j + i] && str[j + i] != SEPARATOR_CHAR)
		i++;
	line->arg1 = (char*)malloc(sizeof(char) * (i + 1));
	while (++k < i)
		line->arg1[k] = str[j + k];
	line->arg1[k] = '\0';
	j += i + 1;
	j = skip_whitespace(str, j);
	line->arg2 = (char*)malloc(sizeof(char) * 4);
	line->arg2[0] = str[j];
	line->arg2[1] = str[j + 1];
	if (str[j + 2] >= '0' && str[j + 2] <= '9')
	{
		line->arg2[2] = str[j + 2];
		line->arg2[3] = '\0';
	}
	else
		line->arg2[2] = '\0';
	line->op_code = 2;
}

void	cmd_st(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 0;
	j = skip_whitespace(str, j);
	line->op_code = 3;
}

void	cmd_add(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 5;
	j = skip_whitespace(str, j);
	line->op_code = 4;
}

void	cmd_sub(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 7;
	j = skip_whitespace(str, j);
	line->op_code = 5;
}

void	cmd_and(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 0;
	j = skip_whitespace(str, j);
	line->op_code = 6;
}

void	cmd_or(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 5;
		j = skip_whitespace(str, j);
	line->op_code = 7;
}

void	cmd_xor(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 7;
		j = skip_whitespace(str, j);
	line->op_code = 8;
}

void	cmd_zjmp(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 0;
		j = skip_whitespace(str, j);
	line->op_code = 9;
}

void	cmd_ldi(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 5;
		j = skip_whitespace(str, j);
	line->op_code = 10;
}

void	cmd_sti(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 7;
		j = skip_whitespace(str, j);
	line->op_code = 11;
}

void	cmd_fork(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 0;
		j = skip_whitespace(str, j);
	line->op_code = 12;
}

void	cmd_lld(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 5;
		j = skip_whitespace(str, j);
	line->op_code = 13;
}

void	cmd_lldi(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 7;
		j = skip_whitespace(str, j);
	line->op_code = 14;
}

void	cmd_lfork(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 0;
		j = skip_whitespace(str, j);
	line->op_code = 15;
}

void	cmd_aff(t_champ *champ, t_line *line, char *str, int j)
{
	champ->size += 5;
		j = skip_whitespace(str, j);
	line->op_code = 16;
}
