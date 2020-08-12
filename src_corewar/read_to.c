/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_to.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:24:38 by jhakala           #+#    #+#             */
/*   Updated: 2020/08/12 14:11:40 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

char	*copy_to_str(char *str, char *buf, int s_len, int i_len)
{
	char	*tmp;
	int		i;
	int		j;

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

char	*reading(int *size, char *file_name, t_mem *mem)
{
	char	*str;
	char	buf[10];
	int		fd;
	int		i;

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
	else
	{
		ft_putstr_fd(file_name, 2);
		ft_putstr_fd("Could not open.\n", 2);
		if (free_memory(mem))
			system("leaks prog");
		exit(0);
	}
	return (str);
}

int		read_to(t_mem *mem)
{
	t_player	*p;
	char		*input;
	int			size;

	p = mem->player;
	while (p)
	{
		size = 0;
		input = reading(&size, p->file_name, mem);
		p->header = (t_header*)malloc(sizeof(t_header));
		ft_memcpy(p->header, input, sizeof(t_header));
		size -= sizeof(t_header);
		if (size != (int)REV(p->header->prog_size) || size > CHAMP_MAX_SIZE)
		{
			ft_putstr_fd("Diff size as header says or too big\n", 2);
			free(input);
			return (1);
		}
		p->input = (char*)malloc(sizeof(char) * size);
		ft_memcpy(p->input, &input[sizeof(t_header)], size);
		free(input);
		p = p->next;
	}
	return (0);
}
