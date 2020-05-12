/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:28:48 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 16:11:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static t_input		*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(argc, argv);
	input = (t_input *)ft_memalloc(sizeof(input));
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	fd = 0;
	input->file_content = read_input_file(fd, &input->file_content_size);
	return (input);
}

int					main(int argc, char **argv)
{
	t_input		*input;

	input = read_input_data(&argc, &argv);
	if (input->opt & format_asm)
		print_asm(input, input->file_content, input->file_content_size);
	else
		print_hex(input->file_content, input->file_content_size);
	free(input->file_content);
	ft_printf("END\n");
	free(input->g_op_tab);
//	free(input);
	return (0);
}
