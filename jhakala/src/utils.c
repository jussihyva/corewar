#include "test.h"
#include "op.h"

char *copy_name(char *original)
{
  int len;
  char *name;
  char cor[] = "cor";

  len = strlen(original);
  name = (char*)malloc(sizeof(char) * (len + 2));
  for (int i = 0; i < len - 1; i++)
    name[i] = original[i];
  for (int i = 0; i < 3; i++)
    name[len - 1 + i] = cor[i];
  name[len + 2] = '\0';
  return (name);
}
