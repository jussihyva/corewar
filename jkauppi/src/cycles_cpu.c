/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycles_cpu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauppi <jkauppi@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 15:00:30 by jkauppi           #+#    #+#             */
/*   Updated: 2020/07/06 15:08:49 by jkauppi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cpu.h"

static int			is_player_alive(t_cpu *cpu, t_player *player)
{
	int				reason_to_kill;

	reason_to_kill = 0;
	cpu->current_number_of_checks++;
	if (!player->is_live)
		reason_to_kill = 1;
	else if (player->is_live >= NBR_LIVE ||
				cpu->current_number_of_checks >= MAX_CHECKS)
	{
		cpu->current_cycle_to_die -= CYCLE_DELTA;
		if (cpu->current_cycle_to_die < 0)
			reason_to_kill = 2;
		cpu->current_number_of_checks = 0;
	}
	player->is_live = 0;
	cpu->next_cycle_to_die_point = cpu->cycle_cnt +
											cpu->current_cycle_to_die;
	ft_printf("  Updated cycle to die cnt: %d\n",
											cpu->current_cycle_to_die);
	return (reason_to_kill);
}

int					execute_cycles(int cycles_to_execute, t_cpu *cpu,
															t_player *player)
{
	int				reason_to_kill;

	reason_to_kill = 0;
	while (cycles_to_execute-- && !reason_to_kill)
	{
		cpu->cycle_cnt++;
		ft_printf("Cycle : %lld (%lld)\n", cpu->cycle_cnt,
						cpu->next_cycle_to_die_point - cpu->cycle_cnt);
		if (cpu->cycle_cnt == cpu->next_cycle_to_die_point)
			reason_to_kill = is_player_alive(cpu, player);
	}
	return (reason_to_kill);
}
