#include <stdio.h>

int main(void)
{
	char i = 0;
	i = 1 << 6;
	i += 2 << 4;
	i += 2 << 2;
	printf("%x\n", i);
	return (0);
}
