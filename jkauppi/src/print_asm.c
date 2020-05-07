/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_asm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 22:39:50 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/07 22:43:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "decoder.h"

void				print_asm(char *file_content, ssize_t size)
{
	char		*p;

	p = file_content;
	while (index < size)
	{
		ft_printf("%08x: ", index);
		ft_printf("\n");
	}
	return ;
}
