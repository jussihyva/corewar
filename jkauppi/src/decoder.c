/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoder.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 11:28:48 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/01 23:12:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

static void		save_input_file(t_input *input, int *argc, char ***argv)
{
	if (*argc > 1)
	{
		if (!(input->opt & map_file))
		{
			input->input_file = ft_strdup((*argv)[1]);
			input->opt |= map_file;
		}
		ft_step_args(argc, argv);
	}
	else
		input->error = input_file_missing;
	return ;
}

static void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-a"))
			input->opt |= format_asm;
		else if (ft_strequ((*argv)[0], "-f"))
			save_input_file(input, argc, argv);
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}

static int			open_fd(t_input *input)
{
	int		fd;

	fd = 0;
	if (input->opt & map_file)
		fd = open(input->input_file, O_RDONLY);
	return (fd);
}

static t_input		*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(argc, argv);
	input = (t_input *)ft_memalloc(sizeof(*input));
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	fd = open_fd(input);
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
//	free(input->g_op_tab);
//	free(input);
	return (0);
}
