/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:10:17 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/25 18:50:33 by jhakala          ###   ########.fr       */
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
# define REV_S(x) ((x << 16) >> 24) | ((x<<24)>>16)

//print functions for testing -> poista
void print_c_lst(t_carriage *c); // carriage.c
void    print_arena(char *arena); // wm_init.c
void	print_p(t_player *p); //main.c

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
void	new_carriage(t_carriage **alst, int place, t_carriage *parent, t_game *game);

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
int		**get_argument_type_codes(int type);
int		possible_arg(int **types, int op_code);
int		read_types(char *arena, int from, int size);
int		arg_sizes(char *arena, int place, int **types, int code);
int		read_game_param(char *arena, int from, int size, int **types);
int		read_statement_code(t_carriage *c, t_game *game, int place);

/*
** game/check.c
*/
int		check_carriages(t_game *game);

/*
** statements/
*/
int		op_live(t_game *game, int place, t_carriage *c);
int		op_ld(t_game *game, int place, t_carriage *c);
int		op_st(t_game *game, int place, t_carriage *c);
int		op_add(t_game *game, int place, t_carriage *c);
int		op_sub(t_game *game, int place, t_carriage *c);
int		op_and(t_game *game, int place, t_carriage *c);
int		op_or(t_game *game, int place, t_carriage *c);
int		op_xor(t_game *game, int place, t_carriage *c);
int		op_zjmp(t_game *game, int place, t_carriage *c);
int		op_ldi(t_game *game, int place, t_carriage *c);
int		op_sti(t_game *game, int place, t_carriage *c);
int		op_fork(t_game *game, int place, t_carriage *c);
int		op_lld(t_game *game, int place, t_carriage *c);
int		op_lldi(t_game *game, int place, t_carriage *c);
int		op_lfork(t_game *game, int place, t_carriage *c);
int		op_aff(t_game *game, int place, t_carriage *c);


t_op		g_op_tab[17];



#endif
