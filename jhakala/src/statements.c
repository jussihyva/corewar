/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:49:52 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/10 19:30:13 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.h"
#include "op.h"

t_type	g_type[17] = {
	{cmd_empty}, {cmd_live}, {cmd_ld}, {cmd_st}, {cmd_add}, {cmd_sub}, {cmd_and}, {cmd_or}, {cmd_xor},
	{cmd_zjmp}, {cmd_ldi}, {cmd_sti}, {cmd_fork}, {cmd_lld}, {cmd_lldi}, {cmd_lfork}, {cmd_aff}  
};

void add_label(t_label **alst, t_label *new)
{
  new->next = *alst;
  *alst = new;
}

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
	printf("LABEL NAME = %s, ", label->name);
	printf("LABEL PLACE = %d\n", label->place);
	return (label);
}

int is_label(char *str)
{
	int i;
	
	i = skip_whitespace(str, 0);
	while (str[i] && is_that_char(str[i], LABEL_CHARS) == 1)
		i++;
	if (str[i] == LABEL_CHAR)
		return (i);
	return (0);
}

/*
** save label names in linked list and byte place from the start
** get what statement it is 1-16, 0 is something different than statement (comment, label, error jne.)
*/

t_label *next_row(t_champ *champ)
{
	t_line *line;
	t_label *lst = NULL;
	int i = 0, j;

	line = champ->lines;
	while (line)
	{
		if ((j = is_label(line->str)) > 0)
		{
			add_label(&lst, new_label(champ, line->str));
			//there might be cmd in the same row as label, if not statement selection returns 0, and row can be deleted
			j = skip_whitespace(line->str, j + 1);
			i = statement_selection(line->str, j);
			g_type[i].f(champ, line, line->str, j);
		}
		else
		{
			i = statement_selection(line->str, 0);
			g_type[i].f(champ, line, line->str, j);
		}
		printf("op_code = %d\n", line->op_code);
		line = line->next;
	}
	return (lst);
}
	  
