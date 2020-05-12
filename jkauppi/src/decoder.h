/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:41:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 15:22:10 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# define BINARY_BUFF_SIZE 2048

typedef enum		e_opt
{
	format_hex = 0x01,
	format_asm = 0x02
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

typedef struct		s_op_param
{
	int				type;
	int				value;
}					t_op_param;

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

typedef struct		s_instruction
{
	char		*start_p;
	ssize_t		length;
	t_opcode	opcode;
	t_op_param	param[3];
}					t_instruction;

typedef struct		s_input
{
	t_opt			opt;
	char			*file_content;
	size_t			file_content_size;
	t_op			*g_op_tab;
}					t_input;

typedef struct		s_asm_code
{
	char			*file_content;
	t_header		*header;
	t_list			**instruction_lst;
}					t_asm_code;

void				read_opt(t_input *input, int *argc, char ***argv);
void				ft_step_args(int *argc, char ***argv);
char				*read_input_file(int fd, size_t *file_content_size);
void				del_elem(void *elem, size_t size);
void				print_hex(char *line, ssize_t size);
void				print_asm(t_input *input, char *file_content, ssize_t size);
void				read_g_op_tab(t_input *input);
void				print_hex_string(ssize_t index, char *line, ssize_t size);
void				print_params(t_op_param *param);
t_asm_code			*parse_instructions(t_input *input, char *file_content,
																ssize_t size);
t_header			*read_header(char *file_content);
void				remove_asm_code(t_asm_code *asm_code);

#endif
