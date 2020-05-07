/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:28:48 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/07 21:09:26 by ubuntu           ###   ########.fr       */
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
	print_hex(input->file_content, input->file_content_size);
	free(input->file_content);
	ft_printf("END\n");
	free(input);
	return (0);
}
