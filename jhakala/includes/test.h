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
  int			place;
  struct s_label *next;
}				t_label;

typedef struct	s_line
{
  char			*str;
  struct s_line	*next;
	int			op_code;
	char		*arg1;
	char		*arg2;
	char		*arg3;
}				t_line;

typedef struct	s_champ
{
  char			*name;
  char			*comment;
  //  t_cmd		*cmd;
  int			size;
  struct s_line *lines;
  struct s_label *labels;
	//tmp
	int			counter;
}				t_champ;

typedef struct	s_type
{
	void		(*f)();
}				t_type;

/*
** utils.c
*/
int			is_that_char(char c, char *str);
int			skip_whitespace(char *str, int i);
char		*copy_name(char *original, int j);

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

/*
** statement.c
*/
t_label		*next_row(t_champ *champ);

/*
** statement_selection.c
*/
int			statement_selection(char *line, int i);

/*
** cmd:s
*/
void		cmd_empty(t_champ *champ, t_line *line, char *str, int j);
void		cmd_live(t_champ *champ, t_line *line, char *str, int j);
void		cmd_ld(t_champ *champ, t_line *line, char *str, int j);
void		cmd_st(t_champ *champ, t_line *line, char *str, int j);
void		cmd_add(t_champ *champ, t_line *line, char *str, int j);
void		cmd_sub(t_champ *champ, t_line *line, char *str, int j);
void		cmd_and(t_champ *champ, t_line *line, char *str, int j);
void		cmd_or(t_champ *champ, t_line *line, char *str, int j);
void		cmd_xor(t_champ *champ, t_line *line, char *str, int j);
void		cmd_zjmp(t_champ *champ, t_line *line, char *str, int j);
void		cmd_ldi(t_champ *champ, t_line *line, char *str, int j);
void		cmd_sti(t_champ *champ, t_line *line, char *str, int j);
void		cmd_fork(t_champ *champ, t_line *line, char *str, int j);
void		cmd_lld(t_champ *champ, t_line *line, char *str, int j);
void		cmd_lldi(t_champ *champ, t_line *line, char *str, int j);
void		cmd_lfork(t_champ *champ, t_line *line, char *str, int j);
void		cmd_aff(t_champ *champ, t_line *line, char *str, int j);

#endif
