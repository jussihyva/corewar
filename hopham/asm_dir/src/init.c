/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 00:15:32 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/28 12:20:20 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
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

void	init_champ(int fd, int *op, char *str)
{
	t_champ	*champ;
	int		r;

	r = 2;
	champ = NULL;
	if (!(champ = (t_champ*)malloc(sizeof(t_champ))))
		return ;
	if (!(champ->name = get_str(fd, NAME_CMD_STRING, &r)))
		return (n_error("Name_error\n", op));
	if (!(champ->comment = get_str(fd, COMMENT_CMD_STRING, &r)))
		return (n_error("Comment_error\n", op));
	champ->size = 0;
	champ->label = NULL;
	if (!(champ->cmd = get_lines(champ, fd, r)))
		return (n_error("Code_empty_error\n", op));
	if (check_champ(champ) == 0 && check_name(&fd, str, op, ".cor") == 1)
		write_to_file(champ, fd);
	if (op[20] == 1)
		system("leaks asm");
}
