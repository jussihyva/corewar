#include "test.h"
#include "op.h"

int calc_size(t_cmd *cmd)
{
	//just placeholder for now
	return (cmd->op_code);
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
	while (++k < cmd->n_arg)
	{
		//need to rev these
		add_arg(&cmd->arg, new_arg(line, &i, j, k));
	}
	//comment for testing
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
	return (j);
}
