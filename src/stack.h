// stack.c
// (C) Bogdan Filipchuk 2012
/* Name for the functions
 *  #define NAME HELLO
 * For config define the datatype as type:
 *  #define TYPE void
 *
 * Set Stack Implementation
 *  #define LIST_STACK
 *    (default ARRAY_STACK)
 */

#ifndef TYPE
    #define TYPE void
#endif

#ifdef LIST_STACK
// Variables
typedef struct {
    TYPE value;
    Item *link;
} Item;
Item *stack = NULL;
int N;

// Initializer
void STACKinit( int max )
{
    N = 0;
}

void list_del_stack( Item *list ) {
    if(list == NULL)return;
    list_del(list.link);
    free(list);
}

void STACKdelete()
{
    list_del_stack(stack);
    stack == NULL;
}

int STACKempty()
{
    Stackdelete();
    return N = 0;
}

int push( long int value )
{
    Item *new = (*Item) malloc(sizeof(Item));
    new->value = value;
    new->link = stack;
    stack = new;
    return ++N;
}

long int pop()
{
    if ( n<=0 ) return 0L;
    Item *old = stack;
    stack = stack->link;
    free(old);
    return --N;
}

void duplicate()
{
    if ( n<=0 ) return;
    push(stack->value);
}

void swap()
{
    if ( n<=1 ) return;
    stack->value ^= stack->link->value;
    stack->link->value ^= stack->value;
    stack->value ^= stack->link->value;
}
#else
#endif
