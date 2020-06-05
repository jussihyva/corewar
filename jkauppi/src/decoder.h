/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:41:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/05 17:33:48 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H
# include "common.h"
# define BINARY_BUFF_SIZE 2048

void				del_elem(void *elem, size_t size);
void				print_hex(char *line, ssize_t size);
void				print_asm(t_input *input, char *file_content, ssize_t size);
t_header			*read_header(char *file_content);
void				remove_asm_code(t_asm_code *asm_code);
t_asm_code			*initialize_asm_code(t_input *input, char *file_content);

#endif
