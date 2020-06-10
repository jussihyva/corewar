/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_labels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hopham <hopham@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 16:09:45 by HoangPham         #+#    #+#             */
/*   Updated: 2020/06/10 12:36:34 by hopham           ###   ########.fr       */
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
        exit(printf("label points to nothing"));
	len = (int)ft_strlen(s);
	if (len < 2 || s[len - 1] != LABEL_CHAR)
		return (0);
	i = 0;
	while (i < len - 1)
	{
		if (ft_strchr(LABEL_CHARS, s[i]) == NULL)
			return (0);
		i++;
	}
	return (1);	
}

static void	set_new_label(t_label **tmp, char *s, int id)
{
	tmp[0] = (t_label*)ft_memalloc(sizeof(t_label));
	tmp[0]->name = ft_strdup(s);
	tmp[0]->unique_id = id;
	tmp[0]-> position = 1;
}

t_label	*set_label(t_label *label, char *s)
{
	t_label	*res;
	t_label	*tmp;
	int		id;

	if (ft_strlen(s) > 0)
		s[ft_strlen(s) - 1] = 0;
	id = 1;
	res = label;
	while (res != NULL && res->next != NULL && ft_strcmp(res->name, s) != 0)
	{
		id++;
		res = res->next;
	}
	if (res != NULL && ft_strcmp(res->next, s) == 0)
		return (res);
	if (res != NULL)
		id++;
	set_new_label(&tmp, s, id);

}

int	get_label(t_data *data, char **tmp, int tmp_len)
{
	t_label	*label;
	int		label_pos;

	label = set_label(data->label, tmp[0]);
}