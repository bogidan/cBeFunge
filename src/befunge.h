// befunge.h
// (C) Bogdan Filipchuk 2012

#ifndef BEFUNGE_h
#define BEFUNGE_h
// Stack implementation
//#include stack.c

enum vmode{ QUIT, INSERT, RUN, PAUSE, DEBUG };

/* Befunge operator list
 *  Specific CHAR values which mean something to the interpreter
 */
enum operators {
    // Directional Operators
    //  Alter the flow of the program
    NORTH = '^',
    EAST = '<',
    SOUTH = 'v',
    WEST = '>',
    IN = 'x',  // reserved for 3D fields
    OUT = 'o', //
    EXIT = '@'
};

// Representation of Direction
enum directions {
    D_NORTH = 0,
    D_EAST  = 1,
    D_SORTH = 2,
    D_WEST  = 3,
};
// Reversal of Direction
#define REVERSE_(dir) dir=(dir+2)%4
#endif

