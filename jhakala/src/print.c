#include "test.h"
#include "op.h"

void	print_line(t_cmd *cmd, int j, int mode)
{
	t_arg *arg;
	arg = cmd->arg;
	printf("name: '%s', ", g_op_tab[j].str);
	printf("op_code: '%d', ", cmd->op_code);
	printf("n_arg: '%d' ", cmd->n_arg);
	for (int i = 0; i < cmd->n_arg; i++)
	{
		if (mode > 0)
		{
			printf("arg%d = '%s', ", i + 1, arg->str);
//			printf("t_arg: %d,", g_op_tab[j].t_arg[i]);
		}
		else
		{
			printf("arg = '%s', ", arg->str);			
//			printf("%d, ", g_op_tab[j].t_arg[i]);
		}
		arg = arg->next;
	}
	printf("\n");
}
