#include <stdint.h>
#include "mipslab.h"

void drawWinScreen(int winner) {
    if (winner == 1) {
        //display_init();
        display_string(0, "Player 1 Wins!");
        display_string(1, "Menu B1");
        display_string(3, "");
        if (previousPage == 2) {
            display_string(2, "Play again B2");
        } else {
            display_string(2, "");
        }
        display_update();
    } else if (winner == 2){
        display_string(0, "Player 2 Wins!");
        display_string(1, "Menu B1");
        display_string(3, "");
        if (previousPage == 2) {
            display_string(2, "Play again B2");
        } else {
            display_string(2, "");
        }
        display_update();
    } else {
        display_string(0, "Draw!");
        display_string(1, "Menu B1");
        display_string(3, "");
        if (previousPage == 2) {
            display_string(2, "Play again B2");
        } else {
            display_string(2, "");
        }
        display_update();
    }
}