/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:30:16 by ubuntu            #+#    #+#             */
/*   Updated: 2020/05/12 11:38:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "decoder.h"

void			ft_step_args(int *argc, char ***argv)
{
	(*argc)--;
	(*argv)++;
	return ;
}

void			read_opt(t_input *input, int *argc, char ***argv)
{
	while (*argc)
	{
		if (ft_strequ((*argv)[0], "-a"))
			input->opt |= format_asm;
		else
			break ;
		ft_step_args(argc, argv);
	}
	return ;
}

static t_list	**read_file_content(int fd, size_t *file_content_size)
{
	char		line[BINARY_BUFF_SIZE];
	t_list		**content_lst;
	t_list		*elem;
	ssize_t		ret;

	content_lst = (t_list **)ft_memalloc(sizeof(*content_lst));
	while ((ret = read(fd, &line, BINARY_BUFF_SIZE)) > 0)
	{
		elem = ft_lstnew(line, sizeof(*line) * ret);
		*file_content_size += ret;
		ft_lstadd_e(content_lst, elem);
	}
	return (content_lst);
}

char			*read_input_file(int fd, size_t *file_content_size)
{
	char		*file_content;
	t_list		**content_lst;
	t_list		*elem;
	size_t		i;

	content_lst = read_file_content(fd, file_content_size);
	file_content = (char *)ft_memalloc(sizeof(*file_content) *
															*file_content_size);
	elem = *content_lst;
	i = 0;
	while (elem)
	{
		ft_memcpy(file_content + i, elem->content, elem->content_size);
		i += elem->content_size;
		elem = elem->next;
	}
	ft_lstdel(content_lst, del_elem);
	free(content_lst);
	return (file_content);
}
