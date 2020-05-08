/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:28:48 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/08 17:22:45 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

int					main(int argc, char **argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(&argc, &argv);
	input = (t_input *)ft_memalloc(sizeof(input));
	read_opt(input, &argc, &argv);
	ft_printf("Format=%d\n", input->opt);
	fd = 0;
	input->file_content = read_input_file(fd, &input->file_content_size);
	if (input->opt & format_asm)
		print_asm(input->file_content, input->file_content_size);
	else
		print_hex(input->file_content, input->file_content_size);
	free(input->file_content);
	ft_printf("END\n");
	free(input);
	return (0);
}
