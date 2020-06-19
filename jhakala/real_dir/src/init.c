/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:15:32 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 02:24:54 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "op.h"
/*
void	add_label(t_label **alst, t_label *new)
{
	new->next = *alst;
	*alst = new;
}

void	add_arg(t_arg **alst, t_arg *new)
{
	new->next = *alst;
	*alst = new;
}

void	add_cmd(t_cmd **alst, t_cmd *new)
{
	new->next = *alst;
	*alst = new;
}
*/
t_champ	*init_champ(int fd)
{
	t_champ *champ;

	champ = NULL;
	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return (NULL);
	champ->name = get_str(fd, NAME_CMD_STRING);
	champ->comment = get_str(fd, COMMENT_CMD_STRING);
	champ->size = 0;
	champ->label = NULL;
//	champ->cmd = get_lines(champ, fp);
	ft_printf("champ->name = '%s'\n", champ->name);
	ft_printf("champ->comment = '%s'\n", champ->comment);
	return (champ);
}
