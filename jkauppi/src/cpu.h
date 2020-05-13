/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:34:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/13 14:07:07 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H
# include "common.h"

typedef struct		s_cpu
{
	int				reg[REG_NUMBER + 1];
	int				is_live;
	char			*PC;
}					t_cpu;

void				exec_live(t_cpu *cpu, t_instruction *instruction);
void				exec_ld(t_cpu *cpu, t_instruction *instruction);
void				exec_zjmp(t_cpu *cpu, t_instruction *instruction);

#endif
