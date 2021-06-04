#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "sprites.h"
#include "mipslab.h"

void drawMenu( void ) {
    display_string(0, "Multiplayer  B4");
    display_string(1, "Singleplayer B3");
    display_string(2, "Highscore    B2");
    display_string(3, "");
    display_update();
}