/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_cpu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:46:25 by jkauppi           #+#    #+#             */
/*   Updated: 2020/06/30 15:47:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

void			print_cpu(t_cpu *cpu, t_input *input,
							t_instruction *instruction, t_asm_code *asm_code)
{
	int			reg;

	print_instruction(input, instruction, asm_code->file_content);
	ft_printf("%85s", "CPU: ");
	reg = 0;
	while (++reg < 8)
		ft_printf(" r%d=%d", reg, cpu->reg[reg]);
	ft_printf(" is_live=%d", cpu->is_live);
	ft_printf(" carry=%d", cpu->carry);
	ft_printf(" cycles_to_die=%d", cpu->current_cycle_to_die);
	ft_printf("\n");
	return ;
}
