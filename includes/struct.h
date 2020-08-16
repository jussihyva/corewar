/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 14:14:20 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/16 16:26:00 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct			s_player
{
	t_header			*header;
	int					id;
	char				*file_name;
	char				*input;
	struct s_player		*next;
}						t_player;

typedef struct			s_carriage
{
	int					owner;
	int					id;
	int					carry;
	int					statement_code;
	int					size;
	int					live_cycle;
	int					remaining_cycle;
	int					place;
	int					reg[16];
	struct s_carriage	*next;
}						t_carriage;

typedef struct			s_game
{
	int					c_nbr;
	struct s_carriage	*c_lst;
	char				*arena;
	int					*owner;
	struct s_player		*last_alive;
	int					total_cycles;
	int					n_live_in_cycle;
	int					cycles_to_die;
	int					n_player;
	t_player			**players;
	int					get_die;
	int					max_check;
	int					print;
	struct s_carriage	*tmp;
}						t_game;

typedef struct			s_mem
{
	char				**av;
	int					dump;
	int					dump_type;
	int					print;
	int					n_player;
	struct s_player		*player;
	t_game				*game;
	int					leaks;
}						t_mem;

typedef struct			s_op
{
	char				*str;
	int					n_arg;
	unsigned char		t_arg[3];
	int					op_code;
	int					n_cycles;
	char				*info;
	int					type;
	int					carriage_maybe;
	int					s_dir;
	int					(*f)();
}						t_op;

#endif
