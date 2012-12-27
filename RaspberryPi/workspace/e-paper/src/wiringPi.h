/*
 * wiringPi.h
 *
 *  Created on: 27.12.2012
 *      Author: siddian
 */

#ifndef WIRINGPI_H_
#define WIRINGPI_H_

#include <inttypes.h>
#include <stdint.h>
#include <stddef.h>

#define LOW 0
#define HIGH 1

#define INPUT 0
#define OUTPUT 1
#define PWM_OUTPUT 2

#define PUD_OFF 0
#define PUD_DOWN 1
#define PUD_UP 2

#ifdef __cplusplus
extern "C" {
#endif

int wiringPiSetup() {
	return 0;
}
int wiringPiSPISetup (int channel, int freq) {
	return 0;
}
void wiringPiSPIDataRW (int channel, uint8_t* buffer, size_t size) {
}

void pinMode (int pin, int mode) {
}
void digitalWrite (int pin, int value) {
}
void pwmWrite (int pin, int value) {
}
int digitalRead (int pin) {
	return 1;
}

void pullUpDnControl (int pin, int pud) {

}

unsigned int millis (void) {
	return 0;
}
void delay (unsigned int howLong) {

}
void delayMicroseconds (unsigned int howLong) {

}

#ifdef __cplusplus
}
#endif

#endif /* WIRINGPI_H_ */