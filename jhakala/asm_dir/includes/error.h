/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 17:02:22 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/20 22:38:43 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# define ARG_ERROR_1 1;
# define ARG_ERROR_2 2;
# define ARG_ERROR_3 3;
# define ARG_ERROR_4 4;
# define ARG_ERROR_5 5;
//# define  6; taken

typedef struct      s_error
{
    char            *str;
}                   t_error;

t_error             g_error[7];

#endif
