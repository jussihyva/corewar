/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:24:38 by jhakala           #+#    #+#             */
/*   Updated: 2020/07/17 16:25:49 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include <stdio.h>

void	prih(t_player *p)
{
	ft_printf("id='%d'\n", p->id);
	ft_printf("magic='%d'\n", REV(p->header->magic));
	ft_printf("name='%s'\n", p->header->prog_name);
	ft_printf("size='%d'\n", REV(p->header->prog_size));
	ft_printf("comment='%s'\n", p->header->comment);
}

char *copy_to_str(char *str, char *buf, int s_len, int i_len)
{
	char *tmp;
	int i;
	int j;

	tmp = (char*)malloc(sizeof(char) * (s_len + i_len + 1));
	i = -1;
	while (++i < s_len)
		tmp[i] = str[i];
	j = -1;
	while (++j < i_len)
		tmp[i++] = buf[j];
	tmp[i] = '\0';
	free(str);
	return (tmp);
}

char *reading(int *size, char *file_name)
{
	char *str;
	char buf[10];
	int fd;
	int i;

	str = NULL;
	if ((fd = open(file_name, O_RDONLY)) > 0)
	{
		str = ft_strnew(0);
		while ((i = read(fd, buf, sizeof(buf) - 1)) > 0)
		{
			buf[i] = '\0';
			str = copy_to_str(str, buf, *size, i);
			*size += i;
		}
	}
	return (str);
}

int		read_to(t_mem *mem)
{
	t_player *p;
	char *input;
	int size;

	p = mem->player;
	while (p)
	{
		size = 0;
		input = reading(&size, p->file_name);

//		for (int i = 0; i < size; i++)
//			ft_printf("%02x, ",(unsigned char)input[i]);
//		ft_printf("\n");

		p->header = (header_t*)malloc(sizeof(header_t));
		ft_memcpy(p->header, input, sizeof(header_t));
		size -= sizeof(header_t);
		p->input = (char*)malloc(sizeof(char) * size);
		ft_memcpy(p->input, &input[sizeof(header_t)], size);
		prih(p);
		free(input);
		for (int i = 0; i < size; i++)
			ft_printf("%02x, ",(unsigned char)p->input[i]);
		ft_printf("\n");

		if (size != REV(p->header->prog_size) || size > CHAMP_MAX_SIZE)
		{
			ft_printf("ERI KOKO || LIIAN ISO\n");
			return (1);
		}

		p = p->next;

	}
	return (0);
}
