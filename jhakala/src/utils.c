#include "test.h"
#include "op.h"

int is_that_char(char c, char *str)
{
  int i;

  i = 0;
  while (str[i] && str[i] != c)
    i++;
  if (str[i] == c)
    return (1);
  return (0);
}

int skip_whitespace(char *str, int i)
{
  while (str[i] && (str[i] == ' ' || str[i] == '	'))
    i++;
  return (i);
}

char *copy_name(char *original, int j)
{
  int len;
  char *name;
  char cor[] = "cor";

  len = strlen(original);
  if (j != 0)
    {
      j = len - 1;
      while (j > 0 && original[j] != '/')
	j--;
      len -= j;
      if (original[j] == '/')
	{
	  j++;
	  name = (char*)malloc(sizeof(char) * (len + 2));
	  for (int i = 0; i < len - 2; i++)
	    name[i] = original[j + i];
	  for (int i = 0; i < 3; i++)
	    name[len - 2 + i] = cor[i];
	  name[len + 2] = '\0';
	  return (name);
	}
    }
  else
    len = strlen(original);
  name = (char*)malloc(sizeof(char) * (len + 2));
  for (int i = 0; i < len - 1; i++)
    name[i] = original[j + i];
  for (int i = 0; i < 3; i++)
    name[len - 1 + i] = cor[i];
  name[len + 2] = '\0';
  return (name);
}
