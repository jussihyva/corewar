/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/12 19:34:42 by ubuntu            #+#    #+#             */
/*   Updated: 2020/07/23 10:56:16 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H
# include "common.h"

t_input				*read_input_data(int *argc, char ***argv);
void				read_opt(t_input *input, int *argc, char ***argv);
void				exec_live(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_ld(t_cpu *cpu, t_process *process, t_instruction *instructio);
void				exec_zjmp(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_sti(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_st(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_ldi(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_sub(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_add(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_or(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_xor(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_and(t_cpu *cpu, t_process *process, t_instruction *instruction);
void				exec_fork(t_cpu *cpu, t_process *process, t_instruction *instruction);
int					execute_cycle(t_cpu *cpu, t_list *process_list,
														size_t num_of_players);
void				print_cpu(t_cpu *cpu, t_input *input, t_process *process,
													t_instruction *instruction);
void				print_memory(t_cpu *cpu);
void				release(t_input *input);
long long			set_cycle_to_die_point(t_cpu *cpu);

#endif
