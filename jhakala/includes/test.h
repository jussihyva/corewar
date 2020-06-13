#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct		s_label
{
	char			*name;
	int				place;
	struct s_label 	*next;
}					t_label;

typedef struct		s_arg
{
	char			*str;
	int				type;
	struct s_arg	*next;
	//maybe
	int				value;
	char			*label;
}					t_arg;

typedef struct		s_cmd
{
	struct s_cmd	*next;
	int				op_code;
//	int				statement_code;
//	int				dir_size;
	int				n_arg;
	struct s_arg	*arg;
}					t_cmd;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	int				size;
	struct s_cmd	*cmd;
	struct s_label	*labels;
}					t_champ;

typedef struct      s_op
{
    char            *str;
	int				size;
    int             n_arg;
    unsigned char	t_arg[3];
    int             op_code;
	// not needed here?
    int             cost;
    char            *extra;
    int             what1;
    int             what2;
}                   t_op;

void				ft_error(char *s1, char *s2);

/*
** utils.c
*/
int					is_label(char *str);
int					is_that_char(char c, char *str);
int					skip_whitespace(char *str, int i);
char				*copy_name(char *original, int j);

/*
** init.c
*/

void				add_label(t_label **alst, t_label *new);
void				add_arg(t_arg **alst, t_arg *new);
void				add_cmd(t_cmd **alst, t_cmd *new);
t_champ				*init_champ(FILE *fp);

/*
** get.c
*/
char				*get_name(FILE *fp);
char				*get_comment(FILE *fp);
t_cmd				*get_lines(t_champ *champ, FILE *fp);

/*
** parse_cmd.c
*/
int					parse_cmd(t_cmd *cmd, char *line, int i);

/*
** parse_arg.c
*/
int					possible_arg(t_arg *arg, int j, int k);
void				parse_arg_type(t_arg *arg);

/*
** op.c
*/
t_op				g_op_tab[17];

/*
** new.c
*/
t_label				*new_label(t_champ *champ, char *str);
t_arg				*new_arg(char *line, int *i, int j, int k);
t_cmd				*new_cmd(t_champ *champ, char *line);

/*
** print.c:s
*/
void	print_line(t_cmd *cmd, int j, int mode);

/*
** looking for place for these
*/
int arg_size(char *line, int *i);; //atm parse_cmd.c

#endif
