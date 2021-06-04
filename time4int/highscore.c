#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>   /* Declarations of uint_32 and the like */
#include "mipslab.h"

void drawHighScore( int score ) {
    display_string(0, "Highscore");
    display_string(1, itoaconv(score));
    display_string(2, "");
    display_string(3, "Menu B1");
    display_update();
}