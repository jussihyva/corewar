/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 16:40:53 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/16 16:27:08 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

void	new_carriage(t_carriage **alst, int place, t_carriage *parent,
					t_game *game)
{
	t_carriage	*new;
	int			i;

	new = (t_carriage*)malloc(sizeof(t_carriage));
	new->place = place;
	new->statement_code = -1;
	new->live_cycle = parent != NULL ? parent->live_cycle : -1;
	new->remaining_cycle = 0;
	new->carry = parent != NULL ? parent->carry : 0;
	new->reg[0] = parent != NULL ? parent->reg[0] : -(game->c_nbr);
	new->owner = parent != NULL ? parent->owner : game->c_nbr;
	new->id = game->c_nbr++;
	i = 0;
	while (++i < 16)
		new->reg[i] = parent != NULL ? parent->reg[i] : 0;
	new->next = *alst;
	*alst = new;
}
