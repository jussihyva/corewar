/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 19:00:15 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/07 19:37:50 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "op.h"

void	cmd_empty(t_champ *champ, char *str)
{
	champ->size += 0;
	printf("here0:%s", str);
}

void	cmd_live(t_champ *champ, char *str)
{
	champ->size += 5;
	printf("here1:%s", str);
}

void	cmd_ld(t_champ *champ, char *str)
{
	champ->size += 7;
	printf("here2:%s", str);
}

void	cmd_st(t_champ *champ, char *str)
{
	champ->size += 0;
	printf("here3:%s", str);
}

void	cmd_add(t_champ *champ, char *str)
{
	champ->size += 5;
	printf("here4:%s", str);
}

void	cmd_sub(t_champ *champ, char *str)
{
	champ->size += 7;
	printf("here5:%s", str);
}

void	cmd_and(t_champ *champ, char *str)
{
	champ->size += 0;
	printf("here6:%s", str);
}

void	cmd_or(t_champ *champ, char *str)
{
	champ->size += 5;
	printf("here7:%s", str);
}

void	cmd_xor(t_champ *champ, char *str)
{
	champ->size += 7;
	printf("here8:%s", str);
}

void	cmd_zjmp(t_champ *champ, char *str)
{
	champ->size += 0;
	printf("here9:%s", str);
}

void	cmd_ldi(t_champ *champ, char *str)
{
	champ->size += 5;
	printf("here10:%s", str);
}

void	cmd_sti(t_champ *champ, char *str)
{
	champ->size += 7;
	printf("here11:%s", str);
}

void	cmd_fork(t_champ *champ, char *str)
{
	champ->size += 0;
	printf("here12:%s", str);
}

void	cmd_lld(t_champ *champ, char *str)
{
	champ->size += 5;
	printf("here13:%s", str);
}

void	cmd_lldi(t_champ *champ, char *str)
{
	champ->size += 7;
	printf("here14:%s", str);
}

void	cmd_lfork(t_champ *champ, char *str)
{
	champ->size += 0;
	printf("here15:%s", str);
}

void	cmd_aff(t_champ *champ, char *str)
{
	champ->size += 5;
	printf("here16:%s", str);
}
