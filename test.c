#include <stdlib.h>
#include <stdio.h>

void Func(char str_arg[100])
{
    printf("%d\n",sizeof(str_arg));
	char str_arg1[100];
	printf("%d\n",sizeof(str_arg1));
}
int main(void)
{
    char str[]="Hello";
    printf("%d\n",sizeof(str));
    printf("%d\n",strlen(str));
    char*p=str;
    printf("%d\n",sizeof(p));
    Func(str);
}