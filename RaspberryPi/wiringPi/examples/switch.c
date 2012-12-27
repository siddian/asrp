
/*
 * switch.c:
 *	Simple test program to test the wiringPi functions
 *	switch test
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main (void)
{
  printf ("Raspberry Pi wiringPi switch test program\n") ;

  if (wiringPiSetup () == -1)
    exit (1) ;

  pinMode (2, OUTPUT) ;

  for (;;)
  {
    printf("LOW\n");
    digitalWrite(2, LOW);
    delay(1000);
    printf("HIGH\n");
    digitalWrite(2, HIGH);
    delay(1000);
  }

  return 0 ;
}
