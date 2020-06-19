#include "test.h"
#include "op.h"

int calc_size(t_cmd *cmd)
{
	int size, i = -1;
	t_arg *arg;
	//op_code: + 1
	size = 1;
	//if statement_code: + 1
	if (cmd->statement_code == 1)
		size += 1;
	arg = cmd->arg;
	while (++i < cmd->n_arg)
	{
		if (arg->type == 1)
			size += 1;
		else if (arg->type == 2)
			size += cmd->dir_size;
		else if (arg->type == 3)
			size += 2;
		arg = arg->next;
	}
	//comment testing
	if (PRI == 1)
		printf("size of cmd: %d\n", size);
	cmd->size = size;
	return (size);
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

int	parse_cmd_to_args(t_cmd *cmd, char *line, int i, int j)
{
	int k = -1;
	
	i += g_op_tab[j].size;
	cmd->n_arg = g_op_tab[j].n_arg;
	cmd->op_code = g_op_tab[j].op_code;
	cmd->statement_code = g_op_tab[j].statement_code;
	cmd->dir_size = g_op_tab[j].dir_size;
	while (++k < cmd->n_arg)
		add_arg(&cmd->arg, new_arg(line, &i, j, k));
	rev_arg(&cmd->arg);
	//comment for testing
	if (PRI == 1)
		print_line(cmd, j, 1);
	return (calc_size(cmd));
}
	
int parse_cmd(t_cmd *cmd, char *line, int i)
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
			return (parse_cmd_to_args(cmd, line, i, j));
		}
		j++;
	}
	free(word);
	return (0);//for error, usually 0
}
