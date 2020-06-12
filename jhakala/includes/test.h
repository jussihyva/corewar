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

typedef struct		s_line
{
	char			*str;
	struct s_line	*next;
	int				op_code;
	int				n_arg;
	char			**arg;
}					t_line;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	int				size;
	struct s_line	*lines;
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

/*
** utils.c
*/
int					is_that_char(char c, char *str);
int					skip_whitespace(char *str, int i);
char				*copy_name(char *original, int j);

/*
** init.c
*/
t_champ				*init_champ(FILE *fp);

/*
** get.c
*/
char				*get_name(FILE *fp);
char				*get_comment(FILE *fp);
t_line				*get_lines(t_champ *champ, FILE *fp);

/*
** statement.c
*/
t_label				*next_row(t_champ *champ);
int					is_label(char *str);
void				add_label(t_label **alst, t_label *new);
t_label				*new_label(t_champ *champ, char *str);

/*
** statement_selection.c
*/
int					statement_selection(t_line *new, char *line, int i);

/*
** op.c
*/
t_op				g_op_tab[17];

/*
** print.c:s
*/
void	print_line(t_line *new, int j, int mode);

#endif
