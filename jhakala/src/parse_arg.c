/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/13 08:11:05 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/13 09:43:44 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "op.h"

int		arg_reg(char *str, int i)
{
	int res = 0;
	
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (str[i] != '\0' || res > 99)
		ft_error("Error: reg_error\n", str);
	return (res);
}

int		arg_dir(char *str, int i)
{
	int res = 0, minus = 1;

	if (str[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		res = res * 10 + (str[i++] - 48);
	if (str[i] != '\0')
		ft_error("Error: dir_error\n", str);
	return (res * minus);
}

char	*arg_dir_label(char *str, int i)
{
	char *res;
	int j = 0;
	
	res = (char*)malloc(sizeof(char) * (strlen(str) - i));
	while (str[i])
		res[j++] = str[i++];
	res[j] = '\0';
	return (res);
}

int		possible_arg(t_arg *arg, int j, int k)
{
	int res = g_op_tab[j].t_arg[k];
	if (arg->type == 1 && (res == 1 || res == 3 || res == 7))
		return (1);
	else if (arg->type == 2 && (res == 2 || res == 3 || res == 6 || res == 7))
		return (1);
	else if (arg->type == 3 && (res == 4 || res == 5 || res == 7))
		return (1);
	printf("%d, %d\n", arg->type, res);
	printf("    ERROR\n ERROR\n ERROR\nparse_arg_type\n");
	return (0);
}		

void	parse_arg_type(t_arg *arg)
{
	if (arg->str[0] == 'r')
	{
		arg->type = 1;
		arg->value = arg_reg(arg->str, 1);
	}
	else if (arg->str[0] == DIRECT_CHAR && arg->str[1] != LABEL_CHAR)
	{
		arg->type = 2;
		arg->value = arg_dir(arg->str, 1);
	}
	else if (arg->str[0] == DIRECT_CHAR && arg->str[1] == LABEL_CHAR)
	{
		arg->type = 2;
		arg->label = arg_dir_label(arg->str, 2);
	}
	else if (arg->str[0] == '-' || (arg->str[0] >= '0' && arg->str[0] <= '9'))
	{
		arg->type = 3;
		arg->value = arg_dir(arg->str, 0);
	}
	else if (arg->str[0] == LABEL_CHAR)
	{
		arg->type = 3;
		arg->label = arg_dir_label(arg->str, 1);
	}
	else
		printf("	ERROR\n	ERROR\n	ERROR\nparse_arg_type\n");
}
