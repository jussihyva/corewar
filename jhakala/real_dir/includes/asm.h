/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 23:21:33 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/21 03:19:34 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include "error.h"

# define OPTION_CHARS "f"

typedef struct		s_label
{
	char			*name;
	int				place;
	struct s_label	*next;
}					t_label;

typedef struct		s_arg
{
	char			*str;
	char			*label;
	int				type;
	int				value;
	int				error;
	struct s_arg	*next;
}					t_arg;

typedef struct		s_cmd
{
	int				op_code;
	int				statement_code;
	int				dir_size;
	int				n_arg;
	int				size;
	int				row;
	int				error;
	struct s_arg	*arg;
	struct s_cmd	*next;
}					t_cmd;

typedef struct		s_champ
{
	char			*name;
	char			*comment;
	int				size;
	struct s_cmd	*cmd;
	struct s_label	*label;
}					t_champ;

typedef struct		s_op
{
	char			*str;
	int				size;
	int				n_arg;
	unsigned char	t_arg[3];
	int				op_code;
	int				statement_code;
	int				dir_size;
}					t_op;

t_op				g_op_tab[17];


/*
** init.c
*/
void				add_label(t_label **alst, t_label *new);
void				add_arg(t_arg **alst, t_arg *new);
void				add_cmd(t_cmd **alst, t_cmd *new);
t_champ				*init_champ(int fd, int *op);

/*
** is.c
*/
int					is_that_char(char c, char *str);
int					is_comment(char *str, int i);
int					is_empty(char *str, int i);
int					is_label(char *str);

/*
** skip.c
*/
int					skip_whitespace(char *str, int i);
int					skip_to(char *str, char c, int i);
int					valid_end(char *str, int i);

/*
** rev.c
*/
void				rev_label(t_label **lst);
int					rev_arg(t_arg **lst);
void				rev_cmd(t_cmd **lst);

/*
** get_head.c
*/
char				*get_str(int fd, char *s1, int *r);

/*
** get_lines.c
*/
t_cmd				*get_lines(t_champ *champ, int fd, int row_n);

/*
** parse_cmd.c
*/
int					parse_cmd(t_cmd *cmd, char *line, int i);

/*
** parse_utils.c
*/
int					calc_cmd_size(t_cmd *cmd);
int					arg_str_size(char *str, int *i);
int					arg_reg(t_arg *arg, char *str, int i);
int					arg_dir(t_arg *arg, char *str, int i);
char				*arg_dir_label(t_arg *arg, char *str, int i);

/*
** check_champ.c
*/
int					check_champ(t_champ *champ);

#endif
