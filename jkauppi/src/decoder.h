/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:41:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/07 23:59:26 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H
# include "libft.h"
# include "ft_printf.h"
# include "op.h"
# define BINARY_BUFF_SIZE 2048

typedef enum				e_opt
{
	format = 1
}							t_opt;

typedef enum				e_opcode
{
	op_lfork = 0x0f,
	op_sti   = 0x0b,
	op_fork  = 0x0c,
	op_lld   = 0x0d,
	op_ld    = 0x02,
	op_add   = 0x04,
	op_zjmp  = 0x09,
	op_sub   = 0x05,
	op_ldi   = 0x0a,
	op_or    = 0x07,
	op_st    = 0x03,
	op_aff   = 0x10,
	op_live  = 0x01,
	op_xor   = 0x08,
	op_lldi  = 0x0e,
	op_and   = 0x06
}							t_opcode;

typedef struct    s_op
{
  char            *instruction_name;
  int             tmp1;
  int             param_type[3];
  t_opcode        opcode;
  int             tmp2;
  char            *description;
  int             tmp4;
  int             tmp5;
}                 t_op;

typedef struct				s_instruction
{
	t_opcode	opcode;
	size_t		length;
}							t_instruction;


typedef struct				s_input
{
	t_opt			opt;
	char			*file_content;
	size_t			file_content_size;
}							t_input;

void			read_opt(t_input *input, int *argc, char ***argv);
void			ft_step_args(int *argc, char ***argv);
char			*read_input_file(int fd, size_t *file_content_size);
void			del_elem(void *elem, size_t size);
void			print_hex(char *line, ssize_t size);
void			print_asm(char *file_content, ssize_t size);

#endif
