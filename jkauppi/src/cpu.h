/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:34:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/03 14:56:02 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CPU_H
# define CPU_H
# include "common.h"

typedef struct		s_cpu
{
	t_op			*g_op_tab;
	long long		cycle_cnt;
	long long		next_cycle_to_die_point;
	int				current_cycle_to_die;
	int				current_number_of_checks;
	char			*memory;
}					t_cpu;

t_input				*read_input_data(int *argc, char ***argv);
void				read_opt(t_input *input, int *argc, char ***argv);
void				exec_live(t_player *player, t_instruction *instruction);
void				exec_ld(t_player *player, t_instruction *instructio);
void				exec_zjmp(t_player *player, t_instruction *instruction);
void				exec_sti(t_player *player, t_instruction *instruction);
void				exec_st(t_player *player, t_instruction *instruction);
void				exec_ldi(t_player *player, t_instruction *instruction);
void				exec_sub(t_player *player, t_instruction *instruction);
void				exec_add(t_player *player, t_instruction *instruction);
void				exec_or(t_player *player, t_instruction *instruction);
void				exec_xor(t_player *player, t_instruction *instruction);
void				exec_and(t_player *player, t_instruction *instruction);
void				exec_fork(t_player *player, t_instruction *instruction);
int					execute_cycles(int cycles_to_execute, t_cpu *cpu,
															t_player *player);
void				print_cpu(t_cpu *cpu, t_input *input, t_player *player,
													t_instruction *instruction);
void				print_memory(t_cpu *cpu);
void				release(t_input *input);

#endif
