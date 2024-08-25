#include <stdio.h>
// CSE1106 Example Source Code
// Demonstrating the call stack with gdb
// gcc -o dead dead.c -Wall -O0 -g
char *p=NULL;
void c()
{
    printf("%c\n",*p);
}
void b()
{
    c();
}
void a()
{
    b();
}
int main(int argc, char *argv[])
{
    a();
    return 0;
}
