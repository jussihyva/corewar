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
  label = (t_label*)malloc(sizeof(label));
  label->place = champ->size;
  label->name = (char*)malloc(sizeof(char) * (i  + 1));
  while (++k < i)
    label->name[k] = str[j + k];
  label->name[k] = '\0';
  return (label);
}

int is_label(char *str)
{
  int i;

  i = skip_whitespace(str, 0);
  while (str[i] && is_that_char(str[i], LABEL_CHARS) == 1)
    i++;
  if (str[i] == LABEL_CHAR)
    return (1);
  return (0);
}
  
t_label *next_row(t_champ *champ)
{
	t_line *line;
	t_label *lst = NULL;
	int i = 0;

	line = champ->lines;
	while (line)
	{
		printf("champ->size:%d\n", champ->size);
		if (is_label(line->str) == 1)
			add_label(&lst, new_label(champ, line->str));
		else
		{
			i = statement_selection(line->str);
			g_type[i].f(champ, line->str);
//			printf("command:%d\n", i);
		}
		line = line->next;
	}
	printf("champ->size:%d\n", champ->size);
	return (lst);
}
	  
