/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:29:07 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 20:18:04 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	rev_label(t_label **lst)
{
	t_label *prev;
	t_label *cur;
	t_label *next;

	prev = NULL;
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*lst = prev;
}

int		rev_arg(t_arg **lst)
{
	t_arg	*prev;
	t_arg	*cur;
	t_arg	*next;
	int		res;

	res = 0;
	prev = NULL;
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*lst = prev;
	return (res);
}

void	rev_cmd(t_cmd **lst)
{
	t_cmd *prev;
	t_cmd *cur;
	t_cmd *next;

	prev = NULL;
	cur = *lst;
	while (cur != NULL)
	{
		next = cur->next;
		cur->next = prev;
		prev = cur;
		cur = next;
	}
	*lst = prev;
}
