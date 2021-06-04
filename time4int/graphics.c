#include <stdint.h>   /* Declarations of uint_32 and the like */

char screenMatrix[128][32];

void drawFrame(){
    int i;
    uint8_t j;
    uint8_t icon[512];
    // i = column number
    for (i = 0; i < 512; i++) {
        uint8_t column = 0;
        // j = pixel number in column
        for (j = 0; j < 8; j++) {
            int x, y;
            x = i % 128;
            y = (i / 128) * 8 + j;  
            column |= (screenMatrix[x][y] << j);
        }
        icon[i] = column;
    }

    display_image(0, icon);   
}

void clearFrame( void ) {
  int x, y;
  for (x = 0; x < 128; x++) {
    for (y = 0; y < 32; y++) {
      screenMatrix[x][y] = 1;
    }
  }
}

void drawGround( void ) {
  int x, y;
  for (x = 0; x < 128; x++) {
    for (y = 0; y < 32; y++) {
      if (y == 31) {
        screenMatrix[x][y] = 0;
      }
      if((( y == 29)  && ((x==6) || (x== 38) || (x==60))) ||
         (( y == 30)  && ((x==5) || (x==6) || (x==7) || (x==38) || (x==59) || (x==60) || (x==78) || (x==111)))){
          screenMatrix[x][y] = 0;
      }
    }
  }
}

void drawSprite(int x, int y, int width, int height, char sprite[width][height]) {
  int i, j;
  for (i = 0; i < width; i++) {
      for (j = 0; j < height; j++) {
          screenMatrix[x + i][y + j] = sprite[i][j];
      }
  }
}