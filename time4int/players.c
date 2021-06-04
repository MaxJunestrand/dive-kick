#include <stdint.h>
#include "mipslab.h"

float player1Posx, player1Posy;
float player2Posx, player2Posy;

float player1dx, player1dy;
float player2dx, player2dy;

float player1accx, player1accy;
float player2accx, player2accy;

char player1enableGrav = 1;
char player2enableGrav = 1;

int player1width = 10;
int player1height = 20;

int player2width = 10;
int player2height = 20;

void player1BackJump( void ) {
    if (playersFrozen) return;
    if (player1IsOnGround) {
        player1dy = -1;
        player1dx = -1;
    }
}

void player1JumpKick( void ) {
    if (playersFrozen) return;
    if (player1IsOnGround) {
        player1dy = -1.35;
    } else if (!isBtn3Pressed){
        player1enableGrav = 0;
        player1dy = 1;
        player1dx = 1;

        if (!isPlayer1Divekicking) {
          player1Posx += 3;
        }
        isPlayer1Divekicking = 1;
    }
        isBtn3Pressed = 1;
}

void player2JumpKick( void ) {
    if (playersFrozen) return;
    if (player2IsOnGround) {
        player2dy = -1.35;
    } else if (!isBtn2Pressed){
        player2enableGrav = 0;
        player2dy = 1;
        player2dx = -1;
        if (!isPlayer2Divekicking) {
          player2Posx -= 3;
        }
        isPlayer2Divekicking = 1;
    }
    isBtn2Pressed = 1;
}

void player2BackJump( void ) {
    if (playersFrozen) return;
    if (player2IsOnGround) {
        player2dy = -1;
        player2dx = 1;
    }
}

void player2AIAggro( void ) {
    char swappedPositions = player2Posx < player1Posx;
    char isHighUp = player2Posy < 7;

    if (player2IsOnGround && !swappedPositions) {
        player2JumpKick();
        isBtn2Pressed = 0;
    } else if (!player2IsOnGround && !swappedPositions && isHighUp) {
        player2JumpKick();
    } else if (swappedPositions) {
        player2BackJump();
    }
}

void player2AIDef( void ) {
    
}