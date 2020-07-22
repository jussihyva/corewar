/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:10:17 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/22 22:14:10 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include "op.h"
# include "struct.h"

# define REV(x) ((x << 24) | (((x>>16)<<24)>>16) | (((x<<16)>>24)<<16) | (x>>24))

//print functions for testing -> poista
void print_c_lst(t_carriage *c); // carriage.c
void    print_arena(char *arena); // wm_init.c

/*
** init.c
*/
t_mem	*ft_init(int ac, char **av);

/*
** parse_av.c
*/
int		parse_av(int ac, char **av, t_mem *mem);

/*
** init.c
*/
int		champ_init(int *arg, int n, int *n_arr, t_mem *mem);

/*
** read_to.c
*/
int		read_to(t_mem *mem);

/*
** wm_init.c
*/
t_game	*wm_init(t_mem *mem);

/*
** carriage.c
*/
void	new_carriage(t_carriage **alst, int place, t_carriage *parent, int id);

/*
** free.c
*/
int		free_int(int *arr);
int		free_memory(t_mem *mem);

/*
** game/run_game.c
*/
int		run_game(t_mem *mem);

/*
** game/game_utils.c
*/
int		read_statement_code(t_carriage *c, t_game *game, int place);

/*
** statements/
*/
void	st(t_game *game, int place, int types[3][2], t_carriage *);

t_op		g_op_tab[17];



#endif
