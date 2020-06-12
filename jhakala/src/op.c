/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2020/06/12 22:16:51 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "test.h"

t_op    g_op_tab[17] =
{
	{"live", 4, 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ldi", 3, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25, "load index", 1, 1},
	{"ld", 2, 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"sti", 3, 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25, "store index", 1, 1},
	{"st", 2, 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6, "et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6, "ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 2, 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6, "ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 4, 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"fork", 4, 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lldi", 4, 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50, "long load index", 1, 1},	
	{"lld", 3, 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lfork", 5, 1, {T_DIR}, 15, 1000, "long fork", 0, 1},	
	{"aff", 3, 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, 0, {0}, 0, 0, 0, 0, 0}
};
