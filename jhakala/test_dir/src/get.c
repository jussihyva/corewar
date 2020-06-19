/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhakala <jhakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/14 00:12:28 by jhakala           #+#    #+#             */
/*   Updated: 2020/06/16 17:29:42 by jhakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "test.h"
#include "op.h"

int		is_is(char *str, int i)
{
	while (str[i] && str[i] != '"')
		i++;
	return (i);
}

char	*get_to_rabbit_ear(FILE *fp, char *str, int i)
{//5min build, probably some errors here and there
	char *line = NULL, *tmp;
	int len, k, m;
	size_t linecap = 0;
	
	while (str[i] && str[i] != '"')
		i++;
	while (str[i] != '"')
	{
		k = 0;
		m = 0;
		getline(&line, &linecap, fp);
		len = strlen(str) + strlen(line);
		tmp = str;
		free(str);
		str = (char*)malloc(sizeof(char) * len);
		while (tmp[k])
		{
			str[k] = tmp[k];
			k++;
		}
		while (line[m])
		{
			str[k + m] = line[m];
			m++;
		}
		while (str[i] && str[i] != '"')
			i++;
	}
	free(line);
	return (str);
}		

int is_not(char *str, int i)
{
	while (str[i] && str[i] != '	' && str[i] != ' ' && str[i] != '\n')
		i++;
	return (i);
}

char	*mod_str(FILE *fp, char *line, char *str)
{
	int i, j = 0, k = 0;
	char *res;

	i = skip_whitespace(line, 0);
	while (str[j])
	{
		if (line[i + j] != str[j])
		{
			ft_error("Error:", str);
			return (0);
		}
		j++;
	}
	i += strlen(str);
	i = skip_whitespace(line, i);
	j = i;
	if (line[i] == '"')
	{//go to matching ", next row if needed and so on
		line = get_to_rabbit_ear(fp, line, i + 1);
		i = is_is(line, i + 1);
		j++;
		//
//		printf("RABBIT: '%s'\n", line);
	}
	else
		i = is_not(line, i);
	res = (char*)malloc(sizeof(char) * (i - j + 1));
	i = i - j;
	while (i > k)
		res[k++] = line[j++];
	res[k] = '\0';
	return (res);
}
	
char *get_name(FILE *fp)
{
  char *line = NULL, *str;
  size_t linecap = 0;

  getline(&line, &linecap, fp);
  //
  str = mod_str(fp, line, NAME_CMD_STRING);
  free(line);
  return(str);
}

char *get_comment(FILE *fp)
{
  char *line = NULL, *str;
  size_t linecap = 0;

  getline(&line, &linecap, fp);
  //
  str = mod_str(fp, line, COMMENT_CMD_STRING);
  free(line);
  return(str);
}

t_cmd *get_lines(t_champ *champ, FILE *fp)
{
  char *line = NULL;
  int i;
  size_t linecap = 0;
  t_cmd *cmd = NULL;

  while ((i = getline(&line, &linecap, fp)) > 0)
  {
	  if (line[0] != '\n' && line[0] != COMMENT_CHAR)
      {
		  if (PRI == 1)
			  printf("----------new line----------\n");
		  add_cmd(&cmd, new_cmd(champ, line));
      }
  }
  free(line);
  rev_cmd(&cmd);
  rev_label(&champ->labels);
  return (cmd);
}
