#include "test.h"
#include "op.h"

void print_lines(t_champ *champ)
{
  t_line *line;
  line = champ->lines;
  while (line)
    {
      printf("%s\n", line->str);
      line = line->next;
    }
}

t_champ *init_champ(FILE *fp)
{
  t_champ *champ;

  champ = (t_champ*)malloc(sizeof(t_champ));
  champ->name = get_name(fp);
  champ->comment = get_comment(fp);
  champ->lines = get_lines(fp);
  //  print_lines(champ);
  champ->size = 0;
  champ->labels = next_row(champ);
  return (champ);
}
