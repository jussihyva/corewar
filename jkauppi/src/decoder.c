/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:28:48 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/02 15:05:13 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-a"))
			input->opt |= format_asm;
		else if (ft_strequ((*argv)[0], "-l"))
			input->opt |= leaks;
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}

static t_input		*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(argc, argv);
	input = (t_input *)ft_memalloc(sizeof(*input));
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	if (*argc)
	{
		fd = open_fd(**argv);
		ft_step_args(argc, argv);
	}
	else
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
	free(input);
	if (input->opt & leaks)
		system("leaks decoder");
	return (0);
}
