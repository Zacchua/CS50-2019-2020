#include <stdio.h>
#include <cs50.h>

int main (void)
{
  string name = get_string("Enter your name?\n");
    printf("hello, %s.\n", name);
}
