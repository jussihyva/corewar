/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 19:13:13 by jhakala           #+#    #+#             */
/*   Updated: 2019/10/30 20:04:00 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_lstprint(t_list *lst)
{
	while (lst)
	{
		ft_lst_content(lst);
		if (lst->next)
			write(1, " --> ", 5);
		lst = lst->next;
	}
}
