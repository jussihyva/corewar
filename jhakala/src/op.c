/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2020/06/13 18:54:36 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "test.h"

t_op    g_op_tab[17] =
{
	{"live", 4, 1, {T_DIR}, 1, 0, 4},
	{"ldi", 3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 1, 2},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 2, 1, 4},
	{"sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 1, 2},
	{"st", 2, 2, {T_REG, T_IND | T_REG}, 3, 1, 4},
	{"add", 3, 3, {T_REG, T_REG, T_REG}, 4, 1, 4},
	{"sub", 3, 3, {T_REG, T_REG, T_REG}, 5, 1, 4},
	{"and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 1, 4},
	{"or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 1, 4},
	{"xor", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 1, 4},
	{"zjmp", 4, 1, {T_DIR}, 9, 0, 2},
	{"fork", 4, 1, {T_DIR}, 12, 0, 2},
	{"lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 1, 2},	
	{"lld", 3, 2, {T_DIR | T_IND, T_REG}, 13, 1, 4},
	{"lfork", 5, 1, {T_DIR}, 15, 0, 2},	
	{"aff", 3, 1, {T_REG}, 16, 1, 4},
	{0, 0, 0, {0}, 0, 0, 0}
};
