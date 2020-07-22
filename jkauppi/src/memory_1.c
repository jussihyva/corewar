/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/22 15:51:09 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void			del_elem(void *elem, size_t size)
{
	(void)size;
	free(elem);
	elem = NULL;
	return ;
}

static void		del_asm_code(void *elem, size_t size)
{
	t_instruction	*instruction;

	(void)size;
	instruction = *(t_instruction **)elem;
	free(instruction);
	free(elem);
	elem = NULL;
	return ;
}

void			remove_asm_code(t_asm_code *asm_code)
{
	ft_lstdel(asm_code->instruction_lst, del_asm_code);
	free(asm_code->instruction_lst);
	free(asm_code->header);
	free(asm_code);
	return ;
}

void			release(t_input *input)
{
	int			i;
	t_x_player	*x_player;

	i = -1;
	while (++i < input->num_of_players)
	{
		x_player = input->x_players[i];
		free(x_player->asm_code->header);
		free(x_player->asm_code->instruction_lst);
		free(x_player->asm_code);
		free(x_player);
	}
	free(input->file_content);
	free(input->x_players);
	free(input);
	return ;
}
