/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:41:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/30 13:33:12 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DECODER_H
# define DECODER_H
# include "common.h"
# define BINARY_BUFF_SIZE 2048

void				del_elem(void *elem, size_t size);
void				print_hex(char *line, ssize_t size);
void				print_asm(t_input *input, char *file_content);
t_header			*read_header(char *file_content);

#endif
