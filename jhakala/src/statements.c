#include "test.h"
#include "op.h"

void add_label(t_label **alst, t_label *new)
{
  new->next = *alst;
  *alst = new;
}

t_label *new_label(t_champ *champ, char *str)
{
  t_label *label;
  int i, j, k;

  i = ski_whitespace(str, 0);
  j = i;
  k = -1;
  while (str[i] && str[i] == LABEL_CHARS)
    i++;
  i -= j;
  label = (t_label*)malloc(sizeof(label));
  label->place = champ->size;
  lable->name = (char*)malloc(sizeof(char) * (j  + 1));
  while (++k < i)
    label->name[k] = line[j + k];
}

int is_label(char *str)
{
  int i;

  i = ski_whitespace(str, 0);
  while (str[i] && str[i] == LABEL_CHARS)
    i++;
  if (str[i] == LABEL_CHAR)
    return (1);
  return (0);
}
  
void next_row(t_champ *champ)
{
  t_line *line;

  line = champ->lines;
  while (line)
    {
      if (is_label(line) == 1)
	{
	  add_label(&lst, new_label(champ, line));
