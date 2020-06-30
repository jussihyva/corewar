/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:18:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/30 14:42:18 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

t_input			*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;

	ft_step_args(argc, argv);
	input = (t_input *)ft_memalloc(sizeof(*input));
	input->num_of_instructions_to_execute = -1;
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	fd = 0;
	input->file_content = read_input_file(fd, &input->file_content_size);
	return (input);
}

void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-v"))
			input->opt |= verbose;
		else if (ft_strequ((*argv)[0], "-f"))
			save_input_file_name(input, argc, argv);
		else if (ft_strequ((*argv)[0], "-p"))
		{
			ft_step_args(argc, argv);
			input->player_number = ft_atoi(*argv[0]);
		}
		else if (ft_strequ((*argv)[0], "-i"))
		{
			ft_step_args(argc, argv);
			input->num_of_instructions_to_execute = ft_atoi(*argv[0]);
		}
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}
