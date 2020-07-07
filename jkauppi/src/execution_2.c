/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 13:47:56 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/07 10:28:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			exec_live(t_player *player, t_instruction *instruction)
{
	player->is_live += 1;
	player->pc = instruction->start_p + instruction->length;
	ft_printf("Live update %d(%d)\n", player->is_live, player->reg[1]);
	return ;
}

void			exec_fork(t_player *player, t_instruction *instruction)
{
	player->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_sti(t_player *player, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	i = 0;
	if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else if (instruction->param[1].type == IND_CODE)
	{
		p = player->pc + instruction->param[1].value;
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
	}
	if (instruction->param[2].type == DIR_CODE)
		i += instruction->param[2].value;
	p = player->pc + i;
	p[0] = (player->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
	p[1] = (player->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
	p[2] = (player->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
	p[3] = (player->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
	player->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_st(t_player *player, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	if (instruction->param[1].type == IND_CODE)
	{
		i = instruction->param[1].value;
		p = player->pc + i;
		p[0] = (player->reg[instruction->param[0].value] >> (8 * 3)) & 0xff;
		p[1] = (player->reg[instruction->param[0].value] >> (8 * 2)) & 0xff;
		p[2] = (player->reg[instruction->param[0].value] >> (8 * 1)) & 0xff;
		p[3] = (player->reg[instruction->param[0].value] >> (8 * 0)) & 0xff;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - player->program_start_ptr +
															sizeof(t_header));
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
	}
	player->pc = instruction->start_p + instruction->length;
	return ;
}
