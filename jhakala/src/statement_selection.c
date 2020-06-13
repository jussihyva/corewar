#include "test.h"
#include "op.h"

int calc_size(t_line *new)
{
	//just placeholder for now
	return (new->op_code);
}
int	arg_size(char *line, int *i)
{
	int len = 0;
	if (line[*i] == SEPARATOR_CHAR)
		(*i)++;
	*i = skip_whitespace(line, *i);
	while (line[*i] != ' ' && line[*i] != '	' && line[*i] != SEPARATOR_CHAR && line[*i] != '\n' && line[*i])
	{
		len++;
		(*i)++;
	}
	return (len);
}

void	add_arg(t_arg **alst, t_arg *new)
{
	new->next = *alst;
	*alst = new;
}

t_arg	*new_arg(char *line, int *i, int j)
{
	int len, m;
	t_arg *arg;

	arg = (t_arg*)malloc(sizeof(t_arg));
	arg->next = NULL;
	len = arg_size(line, &(*i));	
	arg->str = (char*)malloc(sizeof(char) * (len + 1));
	m = -1;
	while (++m < len)
		arg->str[m] = line[*i - len + m];
	arg->str[m] = '\0';
	//lel
	j++;
	return (arg);
}
	
int	new_cmd(t_line *new, char *line, int i, int j)
{
	int k = -1;
	
	i += g_op_tab[j].size;
	new->n_arg = g_op_tab[j].n_arg;
	new->op_code = g_op_tab[j].op_code;
//	new->arg = (char**)malloc(sizeof(char*) * new->n_arg);
	while (++k < new->n_arg)
	{
//need to rev these
		add_arg(&new->arg, new_arg(line, &i, j));
	}
	//comment for testing
	print_line(new, j, 1);
	return (calc_size(new));
}
	
int statement_selection(t_line *new, char *line, int i)
{
	int j = 0;
	char *word;

	word = (char*)malloc(sizeof(char) * 6);
	while (j < 5)
	{
		if (j > 1 && word[j - 1] == '\0')
			word[j] = '\0';
		else
			word[j] = line[i + j];
		j++;
	}
	word[5] = '\0';
	j = 0;
	while (j < 16)
	{
		if (strncmp(word, g_op_tab[j].str, g_op_tab[j].size) == 0)
		{
			free(word);
			return (new_cmd(new, line, i, j));
		}
		j++;
	}
	free(word);
	return (j);
}
