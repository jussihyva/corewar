/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:34:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/06/30 18:08:41 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H
# include "common.h"

typedef struct		s_cpu
{
	long long		cycle_cnt;
	long long		next_cycle_to_die_point;
	char			*program_start_ptr;
	int				reg[REG_NUMBER + 1];
	int				is_live;
	int				carry;
	char			*pc;
	int				current_cycle_to_die;
	int				current_number_of_checks;
	char			*memory;
}					t_cpu;

t_input				*read_input_data(int *argc, char ***argv);
void				read_opt(t_input *input, int *argc, char ***argv);
void				exec_live(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_ld(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_zjmp(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_sti(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_st(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_ldi(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_sub(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_add(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_or(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_xor(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_and(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
void				exec_fork(t_cpu *cpu, t_instruction *instruction,
														t_asm_code *asm_code);
int					execute_cycles(int cycles_to_execute, t_cpu *cpu);
void				print_cpu(t_cpu *cpu, t_input *input,
							t_instruction *instruction, t_asm_code *asm_code);
void				print_memory(t_cpu *cpu);

#endif
