#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

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
}		t_champ;

/*
** utils.c
*/
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
