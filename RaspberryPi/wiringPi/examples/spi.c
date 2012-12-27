
/*
 * spi.c:
 *	Simple test program to test the wiringPi functions
 *	SPI test
 */

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>

int main (void)
{
  int channel = 0;
  uint8_t bufsize = 1;
  uint8_t outbuffer[1] = {'a'};

  if (wiringPiSPISetup (channel, 8000000) < 0) {
    fprintf(stderr, "SPI Setup failed: %s\n", strerror (errno));
    exit(1);
  }
  printf("starting...\n");
  wiringPiSetupSys();

  uint8_t add = 0;
  for (;;) {
    outbuffer[0] = 'a' + add;
    add = ++add % 26;
    wiringPiSPIDataRW (channel, outbuffer, bufsize);
    printf("read from buffer: %c\n", outbuffer[0]);
    delayMicroseconds(500);
  }

  return 0 ;
}
