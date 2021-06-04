#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"

int getbtns( void ) {
  return (PORTD & 0xf0) >> 5;
}

int getbtn1( void ) {
  return (PORTF & 0x2) >> 1;
}