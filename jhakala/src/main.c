#include "test.h"
#include "op.h"

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
  int len;

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
  
int main(int ac, char **av)
{
  FILE		*fp;
  int		fd1, fd2;
  char		*name;
  t_champ	*champ;

  if (ac == 2 && (fd1 = open(av[1], O_RDONLY)) > 0)
    {
      fp = fopen(av[1], "r");
      name = copy_name(av[1]); //av[1].s -> av[1].cor
      fd2 = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644); //if no av[1].cor then make a new, with chmod 644
      //      printf("name = %s, name_len = %zu\n", name, strlen(name));
      champ = init_champ(fp);
      write_to_file(fd2, champ);
    }
  system("leaks prog");
  return (0);
}
