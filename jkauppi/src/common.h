/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:48:41 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/07 16:38:01 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMON_H
# define COMMON_H
# include "errno.h"
# include <fcntl.h>
# include "libft.h"
# include "ft_printf.h"
# include "op.h"

typedef enum		e_opt
{
	format_hex = 0x01,
	format_asm = 0x02,
	verbose = 0x04,
	verbose1 = 0x08,
	leaks = 0x10
}					t_opt;

typedef enum		e_opcode
{
	e_lfork = 0x0f,
	e_sti = 0x0b,
	e_fork = 0x0c,
	e_lld = 0x0d,
	e_ld = 0x02,
	e_add = 0x04,
	e_zjmp = 0x09,
	e_sub = 0x05,
	e_ldi = 0x0a,
	e_or = 0x07,
	e_st = 0x03,
	e_aff = 0x10,
	e_live = 0x01,
	e_xor = 0x08,
	e_lldi = 0x0e,
	e_and = 0x06
}					t_opcode;

typedef enum				e_input_error
{
	file_open_failure = 1,
	input_file_missing
}							t_input_error;

typedef struct		s_op_param
{
	int				type;
	int				value;
}					t_op_param;

typedef struct		s_instruction
{
	char		*start_p;
	ssize_t		length;
	t_opcode	opcode;
	t_op_param	param[3];
}					t_instruction;

typedef struct		s_op
{
	char		*instruction_name;
	int			num_of_params;
	int			param_type[3];
	t_opcode	opcode;
	int			cycles;
	char		*description;
	int			include_coding_byte;
	int			label_size;
}					t_op;

typedef struct		s_asm_code
{
	char			*file_content;
	size_t			file_content_size;
	t_header		*header;
	char			*asa_code;
	int				asa_code_size;
	t_list			**instruction_lst;
}					t_asm_code;

typedef struct		s_player
{
	int				player_number;
	t_asm_code		*asm_code;
	char			*pc;
	char			*program_start_ptr;
	int				reg[REG_NUMBER + 1];
	int				carry;
	int				is_live;
	long long		cycle_point_for_next_instruction;
	t_instruction	*next_instruction;
	int				is_killed;
}					t_player;

typedef struct		s_input
{
	t_input_error	error;
	t_opt			opt;
	char			*file_content;
	size_t			file_content_size;
	t_op			*g_op_tab;
	char			*input_file;
	int				player_number;
	int				num_of_players;
	t_player		**players;
	int				num_of_instructions_to_execute;
}					t_input;

typedef struct		s_cpu
{
	t_opt			opt;
	t_op			*g_op_tab;
	void			(**op_function)(t_player *, t_instruction *);
	int				current_cycle_to_die;
	int				current_number_of_checks;
	char			*memory;
	long long		cycle_cnt;
	long long		cycle_to_die_point;
	size_t			total_num_of_live_instructions;
}					t_cpu;

void				ft_step_args(int *argc, char ***argv);
int					open_fd(char *file_path);
void				read_g_op_tab(t_input *input);
t_cpu				*initialize_cpu(t_input *input);
char				*read_input_file(int fd, size_t *file_content_size);
t_instruction		*parse_instruction(t_cpu *cpu, char *p);
t_asm_code			*parse_instructions(t_input *input, t_cpu *cpu,
											char *file_content, ssize_t size);
void				print_hex_string(ssize_t index, char *line, ssize_t size);
void				print_params(t_op_param *param);
void				print_instruction(t_instruction *instruction,
													long start_ptr, char *name);
t_asm_code			*initialize_asm_code(char *file_content,
													size_t file_content_size);
void				remove_asm_code(t_asm_code *asm_code);

#endif
