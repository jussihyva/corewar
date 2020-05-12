/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 19:32:46 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 16:02:28 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void			del_elem(void *elem, size_t size)
{
	(void)size;
	free(elem);
	elem = NULL;
	return ;
}

static void		del_asm_code(void *elem, size_t size)
{
	t_instruction	*instruction;

	(void)size;
	instruction = *(t_instruction **)elem;
	free(instruction);
	free(elem);
	elem = NULL;
	return ;
}

void			remove_asm_code(t_asm_code *asm_code)
{
	ft_lstdel(asm_code->instruction_lst, del_asm_code);
	free(asm_code->instruction_lst);
	free(asm_code->header);
	free(asm_code);
	return ;
}
