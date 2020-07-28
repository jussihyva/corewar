/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:02:22 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/28 11:51:30 by hopham           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ARG_ERROR_1 1;
# define ARG_ERROR_2 2;
# define ARG_ERROR_3 3;
# define ARG_ERROR_4 4;
# define ARG_ERROR_5 5;
# define ARG_ERROR_6 6;
# define ARG_ERROR_7 7;
# define ARG_ERROR_8 8;

typedef struct		s_error
{
	char			*str;
}					t_error;

/*
** op.c
*/
t_error				g_error[9];

#endif
