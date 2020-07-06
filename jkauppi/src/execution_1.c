/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 09:10:10 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/06 12:40:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			exec_ld(t_player *player, t_instruction *instruction)
{
	if (instruction->param[0].type == DIR_CODE)
	{
		player->reg[instruction->param[1].value] = instruction->param[0].value;
		player->carry = (instruction->param[0].value) ? 0 : 1;
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

static int		save_pointer_value_to_reg(char *p)
{
	int			value;

	value = 0;
	value += p[1] << (8 * 3);
	value += p[2] << (8 * 2);
	value += p[3] << (8 * 1);
	value += p[4] << (8 * 0);
	ft_printf("%x\n", p);
	ft_printf("%d\n", p[0]);
	ft_printf("%d\n", p[1]);
	ft_printf("%d\n", p[2]);
	ft_printf("%d\n", p[3]);
	ft_printf("%d\n", p[4]);
	return (value);
}

void			exec_ldi(t_player *player, t_instruction *instruction)
{
	size_t		i;
	char		*p;

	i = 0;
	if (instruction->param[0].type == DIR_CODE)
		i += instruction->param[0].value;
	else if (instruction->param[0].type == IND_CODE)
	{
		p = player->pc + instruction->param[0].value;
		i += p[0] << (8 * 1);
		i += p[1] << (8 * 0);
	}
	else
		ft_printf("%08x: ", instruction->start_p - player->program_start_ptr +
															sizeof(t_header));
	if (instruction->param[1].type == REG_CODE)
		i += player->reg[instruction->param[1].value];
	else if (instruction->param[1].type == DIR_CODE)
		i += instruction->param[1].value;
	else
		ft_printf("%08p: %p", player->program_start_ptr + sizeof(t_header),
		instruction->start_p - player->program_start_ptr + sizeof(t_header));
	p = player->pc + i;
	player->reg[instruction->param[2].value] = save_pointer_value_to_reg(p);
	player->pc = instruction->start_p + instruction->length;
}

void			exec_sub(t_player *player, t_instruction *instruction)
{
	player->reg[instruction->param[2].value] =
									player->reg[instruction->param[0].value] -
									player->reg[instruction->param[1].value];
	player->carry = (player->reg[instruction->param[2].value]) ? 0 : 1;
	player->pc = instruction->start_p + instruction->length;
	return ;
}

void			exec_add(t_player *player, t_instruction *instruction)
{
	player->reg[instruction->param[2].value] =
									player->reg[instruction->param[0].value] +
									player->reg[instruction->param[1].value];
	player->carry = (player->reg[instruction->param[2].value]) ? 0 : 1;
	player->pc = instruction->start_p + instruction->length;
	return ;
}
