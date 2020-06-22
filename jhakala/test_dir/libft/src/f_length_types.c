/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length_types.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 22:42:25 by jhakala           #+#    #+#             */
/*   Updated: 2020/01/07 00:30:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	h_length(char **str, t_flags *flags)
{
	if (**str == 'h' && *(*str + 1) == 'h')
	{
		*str += 2;
		flags->length_type = 1;
	}
	else
	{
		*str += 1;
		flags->length_type = 2;
	}
}

void	l_length(char **str, t_flags *flags)
{
	if (**str == 'l' && *(*str + 1) == 'l')
	{
		*str += 2;
		flags->length_type = 4;
	}
	else
	{
		*str += 1;
		flags->length_type = 3;
	}
}

void	bigl_length(char **str, t_flags *flags)
{
	*str += 1;
	flags->length_type = 5;
}
