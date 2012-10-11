// main.cpp - initialize the window
// (C) Bogdan Filipchuk 2012

#include "curses.h" // PDcurses library header [Windows]
#include <stdio.h>
#include "befunge.h"

#define TYPE long int
#include "stack.h"

#define ALERT_MAX 200

int y,x; // Store Cursor Position
int w,h; // Width and height of the interpreter set by command-line
enum directions direction; // Direction of the cursor
enum vmode mode; // Stores the Mode of the IDE
char alert_msg[ALERT_MAX]; // Storage for strings
WINDOW *funge; // Holds the rendering of the funge file.
// States
bool del_command = FALSE;

void draw_alert()
{
    /* Draw an alert Window in the center of the screen displaying
     * a message for the user. The message is stored in alert_msg char
     * string
     */
    WINDOW *alert = subwin(stdscr,LINES/3, COLS/2, LINES/4, COLS/4);
    wattron(alert,COLOR_PAIR(1)); // Set border style
    wborder(alert,'|','|','=','=','O','O','O','O'); // Draw border
    wrefresh(alert); // Update Screen
    WINDOW *atext = subwin(stdscr,LINES/3-2,COLS/2-2,LINES/4+1,COLS/4+1);
    wprintw(atext,alert_msg);
    wrefresh(atext);
    getch(); // Wait for Any Key
    delwin(atext); delwin(alert); // Clean Up Alert Windows
}

inline int parse_cmd( int argc, char *argv[] )
{
    /* Parse Arguments for the environment
     *  -s w,h  // Set screen size
     */
    w=0; h=0;
    int i; // int j;
    for(i=1;i<argc;i++){
        if( argv[i][0] == '-' ){
            switch(argv[i][1]){
                if(sscanf( argv[++i], "%d,%d", &w, &h) == 0){
                    goto HELP;
                }
            }
        } else {
    HELP:
            printf(" Help Formating\n");
            printf(" -s w h  // Set screen size");
            return 1;
        }
    }
    return 0;
}

inline void draw_gui()
{
    /* Draw GUIstdscr
     *  -Bar arround the screen
     *  -Current mode
     *  -Cursor Position
     *  -File Name
     */
    attron(COLOR_PAIR(1)); // Strong style
    border('|','|','=','=','O','O','O','O'); // Bar arround screen
    move(LINES-1,2); // Display Current Mode
    switch(mode){
        case INSERT :
            printw("INSERT mode"); break;
        case RUN :
            printw("RUN mode"); break;
        default :
            printw("EXITING cBeFunge"); break;
    }
    getyx( funge, y, x );
    printw("\tCURSOR[x:%d,y:%d]",x,y); // Display Current Position
    move(0,2);
    printw("[file.be]"); // Name of the file editing
    move(1,1);
    refresh();
}

int main( int argc, char **argv )
{
    if( parse_cmd( argc, argv ) == 1 ) return 1; // Parse options
    initscr(); // Init IDE GUI window
    // Create the Funge File window
    funge = subwin( stdscr, h, w, 1, 1);
    // Set terminal settings
    raw();
    noecho();
    keypad( funge, TRUE );

    // Set Up colors
    if( has_colors() == FALSE ) return endwin() + 1;
    start_color();
    init_pair(1,COLOR_GREEN,COLOR_BLACK);
    init_pair(2,COLOR_BLUE,COLOR_WHITE);

    // if w,h are not set use native
    if ( w == 0 || h == 0 ) {
        w = COLS - 2;
        h = LINES - 2; 
    }
    // Set initial cursor position
    x = 0, y = 0;
    // Show Settings
    sprintf(alert_msg,"  BeFunge: programing like no other...\n   Welcome!!!\n  BeFunge Field Size %dx%d\n",w,h);
    draw_alert(); // Show Settings
    erase();

    mode = INSERT; // Default mode is Insert
    /* Start Insert mode
     */
    while( mode != QUIT ){
        draw_gui();
        /* IDE portion inits own sub-window
         *  -Cursor highlight
         *  -displayed cells
         */
        // Highlight Cursor
        mvwchgat( funge, y, x, 1, A_BLINK, 2, NULL);
        wrefresh(funge);
        
        // Act Based on Modes
        switch( mode ) {
            case RUN :
                funge->delaytenths = 50;
                int c = wgetch(funge); // Get Input
                // Undo the Highlight
                mvwchgat( funge, y, x, 1, A_NORMAL, 0, NULL);
                wrefresh(funge); // update screen
                switch(c) {
                    case 'e' : // Edit
                        mode = INSERT;
                        funge->delaytenths = 0;
                        break;
                    case 'r' : // Run again if stoped
                    case 's' : // Stop
                    case 'p' : // Pause
                }
            case PAUSE :
            case DEBUG :
                break;
            case INSERT :
                /* Handle INSERT command
                 * -Wait for input
                 * -Undo highlight
                 * -Process command
                 */
                int c = wgetch(funge); // Get Input
                // Undo the Highlight
                mvwchgat( funge, y, x, 1, A_NORMAL, 0, NULL);
                wrefresh(funge); // update screen
                // Preprocess for complex functions
                if ( del_command ) {
                    REVERSE_(direction);
                    del_command = FALSE;
                }
                // Process the command
                switch( c ) {
                    /* System Options
                     * -Close
                     * -Switch Modes
                     */
                    case KEY_CLOSE : // Handle Quit
                    case KEY_EXIT :
                    case KEY_SUSPEND : // Handle Suspend
                    case KEY_F(4) :
                    case ((int)'c') | BUTTON_CONTROL) :
                    case 27 : // ESC key
                        mode = QUIT; break;
                    case ((int)'r' | BUTTON_CONTROL) : // Switch to Run mode
                        mode = RUN; break;
                    /* Directional Commands
                     * -Directionals
                     * - 'v' '^' '<' '>' commands
                     * - <S-[dir]> commands
                     */
                    case KEY_SUP : // Up Direction
                        c = '^';
                    case '^' :
                        mvwaddch(funge,y,x,c);
                    case KEY_UP :
                        direction = D_NORTH; break;
                    case KEY_SDOWN : // Down Direction
                        c = 'v';
                    case 'v' :
                        mvwaddch(funge,y,x,c);
                    case KEY_DOWN :
                        direction = D_SOUTH; break;
                    case KEY_SRIGHT :
                        c = '>';
                    case '>' :
                        mvwaddch(funge,y,x,c);
                    case KEY_RIGHT :
                        direction = D_EAST; break;
                    case KEY_SLEFT :
                        c = '<';
                    case '<' :
                        mvwaddch(funge,y,x,c);
                    case KEY_LEFT :
                        direction = D_WEST; break;
                    /* Delete Charachters
                     * -On backspace, delete
                     */
                    case KEY_DC :
                    case '\b' : // Backspace Key
                    case KEY_BACKSPACE :
                        REVERSE_(direction);
                        del_command = TRUE;
                        mvwaddch(funge,y,x,erasechar());
                        break;
                    /* Ignore some commands
                     */
                    case '\n' :
                    case '\r' :
                    case '\t' :
                    case '\v' :
                        break; // Ignore these things
                    /* Handle all other Keys
                     */
                    default: 
                        mvwaddch(funge,y,x,c);
                        break;
                }
                break;
            default :
                break;
        }
            case INSERT :
        }
        // Move cursor based on the direction
        switch( direction ) {
            case D_NORTH : y--; y = y<0 ? h-1 : y; break;
            case D_SOUTH : y++; y %= h; break;
            case D_EAST  : x++; x %= w; break;
            case D_WEST  : x--; x = x<0 ? w-1 : x; break;
            default : break;
        }
        wmove(funge,y,x);
    };
    delwin(funge); // clean up funge window
    endwin(); // cleanup GUI window
    // Exit
    printf("\n"); return 0;
};

