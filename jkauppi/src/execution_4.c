/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 14:01:23 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/03 10:30:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_zjmp(t_player *player, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
	{
		if (player->carry)
			player->pc += instruction->param[0].value;
		else
			player->pc = instruction->start_p + instruction->length;
	}
	else
	{
		ft_printf("%08x: ", instruction->start_p - player->program_start_ptr +
															sizeof(t_header));
		print_hex_string(0, instruction->start_p, instruction->length);
		print_params(instruction->param);
		ft_printf("\n");
		player->pc += instruction->param[0].value;
	}
	return ;
}
