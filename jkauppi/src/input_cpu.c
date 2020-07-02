/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:18:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/02 14:51:20 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-v"))
			input->opt |= verbose;
		else if (ft_strequ((*argv)[0], "-l"))
			input->opt |= leaks;
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

static t_input	*initialize_input(void)
{
	t_input		*input;

	input = (t_input *)ft_memalloc(sizeof(*input));
	input->players = (t_player **)ft_memalloc(sizeof(*input->players) *
																MAX_PLAYERS);
	input->num_of_instructions_to_execute = -1;
	return (input);
}

t_input			*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;
	int			i;
	t_player	*player;

	input = initialize_input();
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	i = -1;
	if (*argc)
	{
		while (*argc)
		{
			fd = open_fd(**argv);
			ft_step_args(argc, argv);
			if (fd != -1)
			{
				i++;
				player = (t_player *)ft_memalloc(sizeof(*input->players));
				input->players[i] = player;
				input->file_content = read_input_file(fd,
													&input->file_content_size);
				player->player_number = i + 1;
				player->asm_code =
								initialize_asm_code(input, input->file_content);
			}
			else
				input->file_content = NULL;
		}
	}
	else
	{
		i++;
		player = (t_player *)ft_memalloc(sizeof(*input->players));
		input->players[i] = player;
		input->file_content = read_input_file(0, &input->file_content_size);
		player->asm_code = initialize_asm_code(input, input->file_content);
	}
	input->nuum_of_players = i + 1;
	return (input);
}
