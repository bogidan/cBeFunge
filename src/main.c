// main.cpp - initialize the window
// (C) Bogdan Filipchuk 2012

#include <stdio.h>
#ifndef NO_SDL_SAMPLE // needed for SDL callback sample
	#define _SDL_main_h // hack to keep SDL from messing with main()
	#include <SDL/SDL.h>
#endif
#include "libtcod.h" // libtocd header
#include <windows.h> // standard windows header

int w,h; // Width and height set by the command line

int startGUI(){
    TCOD_console_init_root(w,h,"BeFunge Interpolator",false); // Create the window
	
    vmode mode = start;
    
    while ( !endsim && TCOD_console_is_window_closed() ){
        // Compute events

        // Key Commnads
        TCOD_key_t key = TCOD_console_check_for_keypress(TCOD_KEY_PRESSED);
        if ( key.vk == TCODK_NONE ) continue;
        else if ( key.c == 'i' ) {
            // Enter Insert Mode
        }
    }
	//TCODMouse::showCursor(true);
	
	// Main loop switches through Modes
	// Modes: Menu Console Game
	int i = 0;
	while ( !TCODConsole::isWindowClosed() ){
		// Check for input
		TCOD_key_t key=TCODConsole::checkForKeypress();
		//TCOD_mouse_t mouse=TCODMouse::getStatus();
		//
		if ( key.vk == TCODK_ENTER && key.lalt ) TCODConsole::setFullscreen(!TCODConsole::isFullscreen());
		
		
		// Loop
		TCODConsole::root->printLeft(5,1+(i++),TCOD_BKGND_NONE,"Arrows to move, left mouse button to cast");
		TCODConsole::root->flush();
		// Sleep Function
		TCODSystem::sleepMilli(500);
		
		
		TCODConsole::root->printLeft(5,12,TCOD_BKGND_NONE,"This is a message");
		TCODConsole::root->flush();
		// Sleep Function
		TCODSystem::sleepMilli(500);
	}
	
	TCODConsole::credits(); // Show Credits
	// Close and realase all data
	return 0;
};

}






int main( int argc, char **argv ){
    /* Parse Arguments for the environment
     *  -s w,h  // Set screen size
     */
    int i;
    for(i=1;i<argc;i++){
        if( argv[i][0] == '-' ){
            switch(argv[i][1]){
                if(sscanf( argv[++i], "%d,%d", w, h) == 0){
                    goto HELP;
                }
            }
        } else {
HELP:
            printf(" Help Formating\n");
            printf(" -s w h  // Set screen size");
            return -1;
        }
    }

    // Create the IDE window
    return startGUI();
};





