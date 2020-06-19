/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 23:21:33 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 01:36:27 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>

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
	struct s_arg	*next;
}					t_arg;

typedef struct		s_cmd
{
	int				op_code;
	int				statement_code;
	int				dir_size;
	int				n_arg;
	int				size;
	struct s_arg	*arg;
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
t_champ				*init_champ(int fd);

/*
** utils.c
*/
int					skip_whitespace(char *str, int i);
int					skip_to(char *str, char c, int i);

/*
** get.c
*/
char				*get_str(int fd, char *s1);


#endif
