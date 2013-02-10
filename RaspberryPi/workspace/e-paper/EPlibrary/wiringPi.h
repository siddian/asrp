/*
 * asrp:
 *      Autonomous Stratosphere Return-Plane library
 *      Copyright (c) 2013 Johannes Lächele
 ***********************************************************************
 * This file is part of asrp:
 *      http://code.google.com/p/asrp/
 *
 *    asrp is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    asrp is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with asrp.  If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */

#ifndef WIRINGPI_H_
#define WIRINGPI_H_

/*
 * this is a dummy header file that lets you compile and test programs in a cross-platform compiling scenario.
 * Compiling this on the RPi will include all the correct files with the proper definitions. See below
 */

#ifndef __ARMEL__

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

int wiringPiSetupSys() {
	return 0;
}
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

#else
#include <wiringPi.h>
#include <wiringPiSPI.h>
#endif //__ARMEL__

#endif /* WIRINGPI_H_ */
