/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):
   Arvid Lagerqvist
   Max Junestrand
   24/9/19

   This file modified 2017-04-31 by Ture Teknolog 

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */
#include "graphics.h"
#include "sprites.h"
#include "input.h"
#include "players.h"
#include "highscore.h"

int mytime = 0x5957;

char textstring[] = "text, more text, and even more text!";

volatile int* _PORTE = (volatile int*) 0xbf886110;
volatile int* _TRISE = (volatile int*) 0xbf886100;

float g = 0.1;
char player1IsOnGround = 0;
char player2IsOnGround = 0;

char playersFrozen = 1;

char isPlayer1Divekicking = 0;
char isPlayer2Divekicking = 0;

int page = 0;
int previousPage = 0;

int currentStreak = 0;
int highscore = 0;

char isBtn3Pressed = 0;
char isBtn2Pressed = 0;

char menuDrawn = 0;
char winScreenDrawn = 0;
char highscoreDrawn = 0;

float snowSlowY = 0;
float snowFastY = 0;
float snowSlowV = 0.05;
float snowFastV = 0.08;

char collision( void ) {
  return (player1Posx + player1width >= player2Posx) && (player1Posx < player2Posx + player2width);
}

void switchPage( int pageToSwitchTo ) {
  previousPage = page;
  page = pageToSwitchTo;
}

void updateGame ( void ) {
  // Check if someone won
    if (isPlayer1Divekicking && !isPlayer2Divekicking && collision()) {
      winner = 1;
      win = 1;
    }

    if (isPlayer2Divekicking && !isPlayer1Divekicking && collision()) {
      winner = 2;
      win = 1;
    }

    if (isPlayer2Divekicking && isPlayer1Divekicking && collision()) {
      if (player1Posy < player2Posy) {
        winner = 1;
        win = 1;
      } else if (player2Posy < player1Posy) {
        winner = 2;
        win = 1;
      } else {

      winner = 0;
      win = 1;
      }
    }
    // Check if players are on the ground
    if (player1Posy >= 32 - player1height) {
      player1IsOnGround = 1;
      player1enableGrav = 1;
      isPlayer1Divekicking = 0;
      playersFrozen = 0;
    } else {
      player1IsOnGround = 0;
    }

    if (player2Posy >= 32 - player2height) {
      player2IsOnGround = 1;
      player2enableGrav = 1;
      isPlayer2Divekicking = 0;
      playersFrozen = 0;
    } else {
      player2IsOnGround = 0;
    }

    // Velocity
    player1Posx += player1dx;
    player1Posy += player1dy;

    player2Posx += player2dx;
    player2Posy += player2dy;

    snowSlowY += snowSlowV;
    snowFastY += snowFastV;

    // Gravity acceleration
    if (player1enableGrav) player1dy += g;
    if (player2enableGrav) player2dy += g;

    // Ground friction
    if (player1IsOnGround) {
      player1dx = 0;
    }

    if (player2IsOnGround) {
      player2dx = 0;
    }

    // Ground collision
    if (player1Posy > 32 - player1height) {
      player1Posy = 32 - player1height;
    }

    if (player2Posy > 32 - player2height) {
      player2Posy = 32 - player2height;
    }

    // Right wall
    if (player1Posx > 128 - player1width) {
      player1Posx = 128 - player1width;
    }

    if (player2Posx > 128 - player2width) {
      player2Posx = 128 - player2width;
    }

    // Left wall
    if (player1Posx < 0) {
      player1Posx = 0;
    }

    if (player2Posx < 0) {
      player2Posx = 0;
    }
}

void update() {
  if (page == 1 /* In multiplayer */) {
    updateGame();
  } else if (page == 2 /* In singleplayer */) {
    updateGame();
    // AI decisions
    player2AIAggro();
  } else if (page == 0 /* In menu */) {

  } else if (page == 4 /* Win screen */) {

  }
}

void draw( void ) {
  if (win) {
    if (page == 2) {
      if (winner == 1) {
        currentStreak++;
        if (currentStreak > highscore) {
          highscore = currentStreak;
        }
      }

      if (winner == 2) {
        currentStreak = 0;
      }
    }
    switchPage(4);
    win = 0;
  }

  if (page == 1 || page == 2 /* In game */) {
    clearFrame();
    //drawSprite(0, (int)snowSlowY, 128, 32, snowSprite1);
    //drawSprite(0, (int)snowFastY, 128, 32, snowSprite2);
    //createSnowSprite1();
    //createSnowSprite2();
    if(isPlayer1Divekicking) {
      player1width = 13;
      drawSprite((int)player1Posx, (int)player1Posy, player1width, player1height, player1DiveSprite);      
    } else if (player1IsOnGround) {
      player1width = 10;
      drawSprite((int)player1Posx, (int)player1Posy, player1width, player1height, player1Sprite);
    } else {
      player1width = 11;
      player1height = 20;
      drawSprite((int)player1Posx, (int)player1Posy, player1width, player1height, player1JumpSprite);
    }
    
    if(isPlayer2Divekicking) {
      player2width = 13;
      drawSprite((int)player2Posx, (int)player2Posy, player2width, player2height, player2DiveSprite);      
    } else if (player2IsOnGround) {
      player2width = 10;
      drawSprite((int)player2Posx, (int)player2Posy, player2width, player2height, player2Sprite);
    } else {
      player2width = 11;
      player2height = 20;
      drawSprite((int)player2Posx, (int)player2Posy, player2width, player2height, player2JumpSprite);
    }
    drawGround();
    drawFrame();
  } else if (page == 0 /* In menu */) {
    if (!menuDrawn) {
      clearFrame();
      drawMenu();
      menuDrawn = 1;
    }
  } else if (page == 3 /* Highscore */) {
    if (!highscoreDrawn) {
      clearFrame();
      drawHighScore(highscore);
      highscoreDrawn = 1;
    }
  } else if (page == 4 /* Win screen */) {
    if (!winScreenDrawn) {
      clearFrame();
      drawWinScreen(winner);
      winScreenDrawn = 1;
    }
  }
}

/* Interrupt Service Routine */
void user_isr( void ) {
  if ((IFS(0) >> 8) & 1) {
    update();
    draw();
    //T2IF bit 8 IFS(0) clear interuppt flag
    IFS(0) &= 0xfffffeff;
  }
}

void labinit( void )
{
  display_init();

  //createSnowSprite1();
  //createSnowSprite2();

  PR2 = 31250/6; // timeout every 100ms
  T2CON |= 0x8070; // prescale 256:1
  //*_PORTE &= 0xff;

  TRISF |= 0x2;
  TRISD |= 0xfe0;
  *_TRISE &= ~0xff;

  // interrupts for timer
  //T2IP bit 4:2 IPC(2) priority
  IPC(2) |= 0x1c;
  //T2IS bit 1:0 IPC(2) sub-priority
  IPC(2) |= 0x3;
  //T2IE bit 8 IEC(0) enable timer2 interrupt
  IEC(0) |= 0x100;

  enable_interrupt();
  return;
}

void startGame( int mode ) {
      switchPage(mode);
      // starting values
      player1IsOnGround = 0;
      player2IsOnGround = 0;
      isPlayer1Divekicking = 0;
      isPlayer2Divekicking = 0;
      player1enableGrav = 1;
      player2enableGrav = 1;
      player1Posx = 32;
      player2Posx = 86;
      player1Posy = 0;
      player2Posy = 0;
      player1dx = 0;
      player2dx = 0;
      player1dy = 0;
      player2dy = 0;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  if (page == 1) {
    int btnState = getbtns();
    int btn1State = getbtn1();

    // btn 4: Player one back jump
    if (btnState >> 2) {
      player1BackJump();
    }

    // btn 3: Player 1 straight jump/divekick
    if ((btnState >> 1) & 0x1) {
      player1JumpKick();
    } else {
      isBtn3Pressed = 0;
    }

    // btn 2: Player 2 straight jump/divekick
    if (btnState & 0x1) {
      player2JumpKick();
    } else {
      isBtn2Pressed = 0;
    }

    // btn 1: Player 2 back jump
    if (btn1State) {
      player2BackJump();
    }
  } else if (page == 2) {
    int btnState = getbtns();
    int btn1State = getbtn1();

    // btn 4: Player one back jump
    if (btnState >> 2) {
      player1BackJump();
    }

    // btn 3: Player 1 straight jump/divekick
    if ((btnState >> 1) & 0x1) {
      player1JumpKick();
    } else {
      isBtn3Pressed = 0;
    }
  } else if (page == 0) {
    int btnState = getbtns();

    if (btnState >> 2/* btn 4: start multiplayer */) {
      startGame(1);
    } else if ((btnState >> 1/* btn 3: start singleplayer */) & 0x1) {
      startGame(2);
    } else if (btnState & 0x1 /* btn 2: see highscore */) {
      switchPage(3);
    }
  } else if (page == 3) {
    int btn1State = getbtn1();
    // btn 1: return to menu
    if (btn1State) {
      menuDrawn = 0;
      highscoreDrawn = 0;
      switchPage(0);
      win = 0;
    }
  } else if (page == 4 /* In win screen */) {
    int btn1State = getbtn1();
    int btnState = getbtns();

    // btn 1: return to menu
    if (btn1State) {
      menuDrawn = 0;
      winScreenDrawn = 0;
      switchPage(0);
      win = 0;
    }
     // Play again
    if ((btnState & 0x1) && previousPage == 2) {
      menuDrawn = 0;
      winScreenDrawn = 0;
      startGame(2);
      win = 0;
    }
  }
}

