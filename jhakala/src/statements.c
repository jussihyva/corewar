/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 17:49:52 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/12 22:49:38 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.h"
#include "op.h"

// need to be renamed to ultils2.c or something

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
