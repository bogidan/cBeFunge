// befunge.h
// (C) Bogdan Filipchuk 2012

#ifndef BEFUNGE
#define BEFUNGE
// Stack implementation
#define stack.h

enum vmode{ command; insert; debug; };

typedef struct {
    
} cell;

/* Befunge operator list
 */
enum direction {
    north = '^';
    east = '<';
    south = 'v';
    west = '>';
    in = 'x';
    out = 'o';
    exit = '@';
}

#endif
