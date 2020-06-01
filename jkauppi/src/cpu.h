/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:34:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/14 12:08:42 by ubuntu           ###   ########.fr       */
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

void				exec_live(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_ld(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_zjmp(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_sti(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_ldi(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_sub(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_add(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_or(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);
void				exec_and(t_cpu *cpu, t_instruction *instruction, t_asm_code *asm_code);

#endif