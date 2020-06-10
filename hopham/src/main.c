/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: HoangPham <HoangPham@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 11:31:02 by HoangPham         #+#    #+#             */
/*   Updated: 2020/06/09 11:52:13 by HoangPham        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int main(int ac, char **av)
{
    char    *file_name;
    t_data  *data;

    if (ac < 2) {
        exit(printf("usage: ./asm file_name\n"));
    }
    data = (t_data*)malloc(sizeof(t_data));
    data->fd_read = open(av[ac - 1], O_RDONLY);
}