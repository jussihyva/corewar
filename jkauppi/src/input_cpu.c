/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_cpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 13:18:31 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/29 17:24:32 by jkauppi          ###   ########.fr       */
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
		else if (ft_strequ((*argv)[0], "-n"))
		{
			input->opt |= dump;
			ft_step_args(argc, argv);
			input->player_start_number = ft_atoi(*argv[0]);
		}
		else if (ft_strequ((*argv)[0], "-d"))
		{
			input->opt |= dump;
			ft_step_args(argc, argv);
			input->num_of_instructions_to_execute = ft_atoi(*argv[0]);
			if (!input->num_of_instructions_to_execute)
				input->num_of_instructions_to_execute = -1;
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
	input->player_start_number = 1;
	return (input);
}

static t_player	*initalize_player(int fd, int player_number)
{
	t_player	*player;
	char		*file_content;
	size_t		file_content_size;

	player = (t_player *)ft_memalloc(sizeof(*player));
	file_content_size = 0;
	file_content = read_input_file(fd, &file_content_size);
	player->player_number = player_number;
	player->asm_code = initialize_asm_code(file_content, file_content_size);
	return (player);
}

t_input			*read_input_data(int *argc, char ***argv)
{
	int			fd;
	t_input		*input;
	int			i;
	int			estimated_num_of_players;

	input = initialize_input();
	read_opt(input, argc, argv);
	read_g_op_tab(input);
	i = -1;
	estimated_num_of_players = *argc;
	if (*argc)
	{
		while (*argc)
		{
			fd = open_fd(**argv);
			ft_step_args(argc, argv);
			if (fd != -1)
			{
				i++;
				input->players[i] = initalize_player(fd,
				((i + (input->player_start_number - 1)) %
												estimated_num_of_players) + 1);
			}
		}
	}
	else
		input->players[i] = initalize_player(0, 1);
	input->num_of_players = i + 1;
	return (input);
}
