/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:18:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/22 17:28:42 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-v"))
			input->opt |= verbose;
		else if (ft_strequ((*argv)[0], "-v1"))
			input->opt |= verbose1;
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
	input->x_players = (t_x_player **)ft_memalloc(sizeof(*input->x_players) *
																MAX_PLAYERS);
	input->process_list = (t_process **)ft_memalloc(sizeof(*input->process_list) *
																MAX_PLAYERS);
	input->num_of_instructions_to_execute = -1;
	return (input);
}

static t_x_player	*initalize_player(int fd, int player_number)
{
	t_x_player	*x_player;
	char		*file_content;
	size_t		file_content_size;

	x_player = (t_x_player *)ft_memalloc(sizeof(*x_player));
	file_content_size = 0;
	file_content = read_input_file(fd, &file_content_size);
	x_player->player_number = player_number;
	x_player->asm_code = initialize_asm_code(file_content, file_content_size);
	return (x_player);
}

t_input			*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;
	int			i;

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
				input->x_players[i] = initalize_player(fd, i + 1);
			}
		}
	}
	else
		input->x_players[i] = initalize_player(0, 1);
	input->num_of_players = i + 1;
	return (input);
}
