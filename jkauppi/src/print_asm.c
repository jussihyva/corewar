/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/08 00:20:52 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void				print_asm(char *file_content, ssize_t size)
{
	char		*p;
	char		*end_p;

	end_p = file_content + size;
	p = file_content;
	while (p < end_p)
	{
		ft_printf("%08p: ", p);
		ft_printf("\n");
	}
	return ;
}
