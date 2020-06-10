/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: HoangPham <HoangPham@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 10:49:14 by HoangPham         #+#    #+#             */
/*   Updated: 2020/06/09 16:13:19 by HoangPham        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _ASM_H
# define _ASM_H

#include "op.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft.h"
#include "ft_printf.h"

# define T_DIR_SIZE     (int[]){4, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 4, 2, 2, 4}
# define NUM_OF_ARGS    (int[]){1, 2, 2, 3, 3, 3, 3, 3, 1, 3, 3, 1, 2, 3, 1, 1}  
# define INC_COD_BYTE   (int[]){0, 1, 1, 1, 1, 1, 1 ,1, 0, 1, 1, 0, 1, 1, 0, 1}
# define ALLOWED_ARG_CHARS  "abcdefghijklmnopqrstuvwxyz_0123456789-:%"
# define ALLOWED_DIR_CHARS  "0123456789-"
# define ALT_COMMENT_CHAR    ';'

typedef struct  s_label
{
    int             unique_id;
    int             position;
    char            *name;
    struct s_label  *next;
}               t_label;

typedef struct  s_data
{
    int     fd_read;
    int     fd_write;
    int     total_size;
    char    *name;
    char    *comment;
    t_label *label;
}               t_data;

#endif