/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:40:53 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/24 21:07:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	print_c_lst(t_carriage *c)
{
	int i;

	while (c)
	{
		ft_printf("______NEW_CARRIAGE______\n");
		ft_printf("id = %d\ncarry = %d\nstatement_code = %d\nlive_cycle = %d\nremaining_cycle = %d\nplace = %d\n", c->id, c->carry, c->statement_code, c->live_cycle, c->remaining_cycle, c->place);
		i = 0;
		ft_printf("n:  ");
		while (i < 16)
			ft_printf("%4d", i++);
		i = 0;
		ft_printf("\nreg: ");
		while (i < 16)
			ft_printf("[%d],", c->reg[i++]);
		ft_printf("\n");
		c = c->next;
	}
}

void	new_carriage(t_carriage **alst, int place, t_carriage *parent, t_game *game)
{
	t_carriage *new;
	int i;

	new = (t_carriage*)malloc(sizeof(t_carriage));
	new->place = place;
	new->statement_code = -1;
	new->live_cycle = parent != NULL ? parent->live_cycle : -1;
	new->remaining_cycle = 0;
	new->carry = parent != NULL ? parent->carry : 0;
	new->reg[0] = parent != NULL ? parent->reg[0] : -(game->c_nbr);
	new->id = game->c_nbr++;
	i = 0;
	while (++i < 16)
		new->reg[i] = parent != NULL ? parent->reg[i] : 0;
	new->next = *alst;
	*alst = new;
}

		
	
