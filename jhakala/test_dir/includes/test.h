/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/22 21:10:17 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/13 18:54:00 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H

# include "../libft/includes/ft_printf.h"
# include "../libft/includes/get_next_line.h"
# include <fcntl.h>
# include <stdlib.h>
# include "op.h"
# include "struct.h"

# define REV(x) ((x << 24) | (((x>>16)<<24)>>16) | (((x<<16)>>24)<<16) | (x>>24))

/*
** init.c
*/
t_mem	*ft_init(int ac, char **av);

#endif
