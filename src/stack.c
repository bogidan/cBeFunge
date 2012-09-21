// stack.c
// (C) Bogdan Filipchuk 2012
#include "stack.h"
typedef long int Item;

Item *stack;
int N;

void STACKinit( int max )
{
    stack = malloc( max*sizeof(Item));
    N = 0;
}

int STACKempty()
{
    return N = 0;
}

int push( Item item )
{
    stack[N++] = item;
}

Item pop()
{
    return stack[--N];
}

void duplicate()
{
    stack[N++] = stack[N-1];
}

void swap()
{
    Item C = stack[N];
    stack[N] = stack[N-1];
    stack[N-1] = C;
}
