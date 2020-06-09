/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: HoangPham <HoangPham@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:09:45 by HoangPham         #+#    #+#             */
/*   Updated: 2020/06/09 16:13:48 by HoangPham        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

/*
** @desc	check whether the received string refers to a label or not
** @param	char		*s		- string
** @return	int					- true or false
*/

int is_label(char *s)
{
    int i;
    int len;

    if (!s)
    {
        exit(printf("label points to nothing"));
        len = (int)ft_strlen(s);
    }
}