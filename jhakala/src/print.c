#include "test.h"
#include "op.h"

void	print_line(t_line *new, int j, int mode)
{
	printf("name: '%s', ", g_op_tab[j].str);
	printf("op_code: '%d', ", new->op_code);
	printf("n_arg: '%d' ", new->n_arg);
	for (int i = 0; i < new->n_arg; i++)
	{
		if (mode > 0)
		{
			printf("arg[%d] = '%s', ", i, new->arg[i]);
			printf("t_arg: %d,", g_op_tab[j].t_arg[i]);
		}
		else
		{
			printf("'%s', ", new->arg[i]);
			printf("%d, ", g_op_tab[j].t_arg[i]);
		}
	}
	printf("\n");
}
