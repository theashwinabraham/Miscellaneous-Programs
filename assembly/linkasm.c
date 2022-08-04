/*
* AUTHOR: ASHWIN ABRAHAM
*/

/* This code demonstrates the ability to call assembly code (un clib.asm) in a C program */

#include <stdio.h>

int fact_rec(int);
int fact_loop(int);

int main(int argc, char** argv)
{
    while(1)
    {
        int x;
        scanf("%d", &x);
        printf("%d\n%d\n", fact_loop(x), fact_rec(x));
    }
}