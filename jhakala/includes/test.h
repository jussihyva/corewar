#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct	s_label
{
  char		*name;
  int		place;
}		t_label;

typedef struct	s_line
{
  char		*str;
  struct s_line	*next;
}		t_line;

typedef struct	s_champ
{
  char		*name;
  char		*comment;
  //  t_cmd		*cmd;
  int		size;
  struct s_line *lines;
  struct s_line *labels;
}		t_champ;

/*
** utils.c
*/
int		skip_whitespace(char *str, int i);
char		*copy_name(char *original);

/*
** init.c
*/
t_champ		*init_champ(FILE *fp);

/*
** get.c
*/
char		*get_name(FILE *fp);
char		*get_comment(FILE *fp);
t_line		*get_lines(FILE *fp);

#endif
