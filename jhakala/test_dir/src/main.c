/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/07 05:28:40 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/16 17:49:27 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "op.h"

void	ft_error(char *s1, char *s2)
{
	//when i get time, i'll but better error messages and places where it happens and why
	int i = 0;

	while (s1[i])
		write(2, &s1[i++], 1);
	while (s2[i])
		write(2, &s2[i++], 1);
	write(2, "\n", 1);
}

void write_byte(int fd, int str, int len)
{
	unsigned char content[len];
  	
  for (int i = len - 1; i > -1; i--) {
    content[i] = (unsigned char)str;
    str >>= 8;
  }
  for (int i = 0; i < len; i++) {
    write(fd, &content[i], 1);
    //    printf("%i,", content[i]); //testing
  }
}

void write_to_file(int fd, t_champ *champ)
{
	int	len;

  write_byte(fd, COREWAR_EXEC_MAGIC, 4); //add magic number, os that it is read as a binary, without it -> read as text file
  len = strlen(champ->name);
  for (int i = 0; i < len; i++) //champs name
    write_byte(fd, champ->name[i], 1);
  for (int i = len; i < PROG_NAME_LENGTH; i++) //rest of name_length is put to zero bytes
    write_byte(fd, 0, 1);
  for (int i = 0; i < 4; i++) //contol point of 4 zeros
    write_byte(fd, 0, 1);
  write_byte(fd, champ->size, 4);
  len = strlen(champ->comment);
  for (int i = 0; i < len; i++) //champs comment
    write_byte(fd, champ->comment[i], 1);
  for (int i = len; i < COMMENT_LENGTH; i++) //rest of comment_length is put to zero bytes
	  write_byte(fd, 0, 1);
  for (int i = 0; i < 4; i++) //contol point of 4 zeros
    write_byte(fd, 0, 1);
  //  printf("%s\n%s\n%d\n", champ->name, champ->comment, champ->size);
}

void	write_reg(int fd, t_arg *arg)
{
	write_byte(fd, arg->value, 1);
}

void	write_dir(int fd, t_arg *arg, int i, t_champ *champ)
{
	t_label *label;

	label = champ->labels;
	if (!arg->label)
		write_byte(fd, arg->value, i);
	else
	{
		while (label)
		{
			if (strcmp(label->name, arg->label) == 0)
				break ;
			label = label->next;
		}
		if (label == NULL)
			printf("ERROR:NO LABEL NAME\n");
		else
			write_byte(fd, label->place - champ->size, i);
	}
}

void	write_cmd_to_file(int fd, t_champ *champ)
{
	t_cmd *cmd;
	t_arg *arg;
	int statement_code;

	cmd = champ->cmd;
	arg = cmd->arg;
	while (cmd)
	{
		if (cmd->op_code != 0)
		{
			write_byte(fd, cmd->op_code, 1);
			if (cmd->statement_code == 1)
			{
				arg = cmd->arg;
				statement_code = 0;
				for (int i = 3; i > 0; i--)
				{
					if (arg)
					{
						statement_code += arg->type << (i * 2);
						arg = arg->next;
					}
				}
				write_byte(fd, statement_code, 1);
			}
			arg = cmd->arg;
			while (arg)
			{
				if (arg->type == 1)
					write_reg(fd, arg);
				else if (arg->type == 2)
					write_dir(fd, arg, cmd->dir_size, champ);
				else if (arg->type == 3)
				{//still missing
					write_dir(fd, arg, 2, champ);
//					printf("placeholder\n");
				}
				arg = arg->next;
			}
		}
		champ->size += cmd->size;
		cmd = cmd->next;
	}
}

int main(int ac, char **av)
{
    FILE *fp;
  int		fd1, fd2;
  char		*name;
  t_champ	*champ;

  if (ac == 2 && (fd1 = open(av[1], O_RDONLY)) > 0)
  {
      fp = fopen(av[1], "r");
      name = copy_name(av[1], 1); //av[1].s -> av[1].cor // 0->same directory as original, 0 != atm directory
      fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644); //if no av[1].cor then make a new, with chmod 644
      //      printf("name = %s, name_len = %zu\n", name, strlen(name));
      champ = init_champ(fp);
      write_to_file(fd2, champ);
	  champ->size = 0;
	  write_cmd_to_file(fd2, champ);
    }
  if (PRI == 1)
	  system("leaks prog");
  return (0);
}
