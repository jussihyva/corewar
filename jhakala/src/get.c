#include "test.h"
#include "op.h"

char *get_name(FILE *fp)
{
  char *line = NULL, *str;
  int i;
  size_t linecap = 0;

  i = getline(&line, &linecap, fp);
  str = (char*)malloc(sizeof(char) * (i - 8));
  for (int j = 0; j < i - 9; j++)
    str[j] = line[j + 7];
  str[i - 9] = '\0';
  free(line);
  return(str);
}

char *get_comment(FILE *fp)
{
  char *line = NULL, *str;
  int i;
  size_t linecap = 0;

  i = getline(&line, &linecap, fp);
  str = (char*)malloc(sizeof(char) * (i - 11));
  for (int j = 0; j < i - 12; j++)
    str[j] = line[j + 10];
  str[i - 12] = '\0';
  free(line);
  return(str);
}

void rev_lines(t_line **lst)
{
  t_line *prev;
  t_line *cur;
  t_line *next;

  prev = NULL;
  cur = *lst;
  while (cur != NULL)
    {
      next = cur->next;
      cur->next = prev;
      prev = cur;
      cur = next;
    }
  *lst = prev;
}

void add_line(t_line **alst, t_line *new)
{
  new->next = *alst;
  *alst = new;
}

t_line *new_line(t_champ *champ, char *line)
{
  t_line *new;
  int j, i;

  new = (t_line*)malloc(sizeof(t_line));
  new->next = NULL;
  if ((j = is_label(line)) > 0)
  {
	  add_label(&champ->labels, new_label(champ, line));
	  j = skip_whitespace(line, j + 1);
	  i = statement_selection(new, line, j);
	  champ->size += i;
//	  printf("parse + cmd.I = %d\n", i);
  }
  else
  {
	  j = skip_whitespace(line, 0);
	  i = statement_selection(new, line, j);
	  champ->size += i;
//	  printf("cmd.I = %d\n", i);
  }
  return (new);
}

t_line *get_lines(t_champ *champ, FILE *fp)
{
  char *line;
  int i;
  size_t linecap = 0;
  t_line *lines = NULL;
  
  while ((i = getline(&line, &linecap, fp)) > 0)
  {
	  if (line[0] != '\n' && line[0] != COMMENT_CHAR)
      {
		  add_line(&lines, new_line(champ, line));
      }
  }
  free(line);
  rev_lines(&lines);
  return (lines);
}
