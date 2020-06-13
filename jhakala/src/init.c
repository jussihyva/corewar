/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 08:17:27 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/14 00:17:02 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.h"
#include "op.h"

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

t_champ	*init_champ(FILE *fp)
{
	t_champ *champ = NULL;
	
	champ = (t_champ*)malloc(sizeof(t_champ));
	champ->name = get_name(fp);
	champ->comment = get_comment(fp);
	champ->size = 0;
	champ->labels = NULL;
	printf("champ->name:'%s', champ->comment:'%s'\n", champ->name, champ->comment);
	champ->cmd = get_lines(champ, fp);
	return (champ);
}
