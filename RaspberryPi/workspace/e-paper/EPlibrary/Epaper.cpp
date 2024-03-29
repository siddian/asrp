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

#include "Epaper.hpp"

#include "wiringPi.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

Epaper::Epaper() {
	mRunning = true;
	//TODO: read this from a config file
	mChannel = 0;
	mFreq = 16000000;
	mPWMPin = 1;//only available hardware PWM pin!
	mENPin = 2;
	mCSPin = 3;
	mRSTPin = 4;
	mBUSYPin = 5;
	mDCPin = 6;

	if (wiringPiSetup() < 0) {
		mRunning = false;
		fprintf(stderr, "Wiring Setup failed: %s\n", strerror (errno));
	}

	if (wiringPiSPISetup (mChannel, mFreq) < 0) {
		mRunning = false;
		fprintf(stderr, "SPI Setup failed: %s\n", strerror (errno));
	}

	if (mRunning) {
		pinMode(mENPin, OUTPUT);
		digitalWrite(mENPin, LOW);

		pinMode(mCSPin, OUTPUT);
		digitalWrite(mCSPin, HIGH);

		pinMode(mRSTPin, OUTPUT);
		digitalWrite(mRSTPin, LOW);

		pinMode(mDCPin, OUTPUT);
		digitalWrite(mDCPin, LOW);

		pinMode (mPWMPin, PWM_OUTPUT);
	    pwmWrite(mPWMPin, 0);

		pinMode(mBUSYPin, INPUT);
	}
}

Epaper::~Epaper() {

}

//defined on page 15
void Epaper::sendData(uint8_t registerIndex, uint8_t* data, size_t datasize) {
	//helper variables
	uint8_t msg[1] = {0x70};

	//lets start
	digitalWrite(mCSPin, HIGH);
	//from documentation, setting it to a lower value does not increase performance!
	delayMicroseconds(10);
	digitalWrite(mCSPin, LOW);
	//header
    wiringPiSPIDataRW (mChannel, msg, 1);
    //index
    msg[0] = registerIndex;
    wiringPiSPIDataRW (mChannel, msg, 1);
    //switch enable off and on again
	digitalWrite(mCSPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(mCSPin, LOW);
	//second header
    msg[0] = 0x72;
    wiringPiSPIDataRW (mChannel, msg, 1);
	//now send the actual data!
    for (unsigned i = 0; i < datasize; i++) {
        msg[0] = data[i];
        wiringPiSPIDataRW (mChannel, msg, 1);
    }

	digitalWrite(mCSPin, HIGH);
}


//defined on page 18
void Epaper::powerOn() {
	if (!mRunning) {
		return;
	}
	//make sure we meet start conditions
	digitalWrite(mENPin, LOW);
	digitalWrite(mRSTPin, LOW);
	digitalWrite(mCSPin, LOW);
	digitalWrite(mENPin, LOW);

	//put 50% duty cycle on the pwm output
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delay(5);
    pwmWrite(mPWMPin, 0);
    //enable the display
    digitalWrite(mENPin, HIGH);
    //let the PWm continue for additional 10ms
    pwmWrite(mPWMPin, 512);
    //for at least 10ms
    delay(10);
    pwmWrite(mPWMPin, 0);
    //before switching on the CS pin
    digitalWrite(mCSPin, HIGH);
    //we do not have a BORDER pin so skip this
    //digitalWrite(mBORDERPin, HIGH);
    //but enable reset
    digitalWrite(mRSTPin, HIGH);
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delay(5);
    pwmWrite(mPWMPin, 0);
    //before switching it off
    digitalWrite(mRSTPin, LOW);
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delay(5);
    pwmWrite(mPWMPin, 0);
    //before switching it on again
    digitalWrite(mRSTPin, HIGH);
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delay(5);
    pwmWrite(mPWMPin, 0);
}

//defined on page 19
//COG = Chip on glass
void Epaper::initCOGDriver() {
	if (!mRunning) {
		return;
	}
	//helper variables
	uint8_t data[16];

	//channel select:
	memset(data, 0, 16);
	data[0] = 0x00;
	data[1] = 0x00;
	data[2] = 0x00;
	data[3] = 0x7F;
	data[4] = 0xFF;
	data[5] = 0xFE;
	data[6] = 0x00;
	data[7] = 0x00;
	sendData(0x01, data, 8);

	//DC/DC frequency setting:
	memset(data, 0, 16);
	data[0] = 0xFF;
	sendData(0x06, data, 1);

	//high power mode osc setting:
	memset(data, 0, 16);
	data[0] = 0x9D;
	sendData(0x07, data, 1);

	//disable ADC:
	memset(data, 0, 16);
	sendData(0x08, data, 1);

	//set VCOM level:
	memset(data, 0, 16);
	data[0] = 0xD0;
	data[1] = 0x00;
	sendData(0x09, data, 2);

	//gate and source voltage level:
	memset(data, 0, 16);
	sendData(0x04, data, 1);

	//Driver latch on (cancel register noise):
	memset(data, 0, 16);
	data[0] = 0x01;
	sendData(0x03, data, 1);

	//Driver latch off:
	memset(data, 0, 16);
	sendData(0x03, data, 1);

	//start chargepump positive V
	memset(data, 0, 16);
	data[0] = 0x01;
	sendData(0x05, data, 1);

	//start pwm signal
    pwmWrite(mPWMPin, 512);
    //for at least 30ms
    delay(30);
    pwmWrite(mPWMPin, 0);

	//start chargepump negative V
	memset(data, 0, 16);
	data[0] = 0x03;
	sendData(0x05, data, 1);

	//delay for 30ms
    delay(30);

	//start chargepump vcom driver to on
	memset(data, 0, 16);
	data[0] = 0x0F;
	sendData(0x05, data, 1);

	//delay for 30ms
    delay(30);

	//output enable to disable
	memset(data, 0, 16);
	data[0] = 0x24;
	sendData(0x02, data, 1);

	//from this point on the display pattern is expected
}

void Epaper::writeImage(EpaperImage &image) {
	//helper variables
	uint8_t data[16];
	uint8_t* line;
	for (unsigned y = 0; y < ResY; y++) {
		//set chargepump voltage level reduce voltage shift
		memset(data, 0x00, 16);
		sendData(0x04, data, 1);
		//send init again
		memset(data, 0, 16);
		data[0] = 0x00;
		data[1] = 0x00;
		data[2] = 0x00;
		data[3] = 0x7F;
		data[4] = 0xFF;
		data[5] = 0xFE;
		data[6] = 0x00;
		data[7] = 0x00;
		sendData(0x0A, data, 8);
		line = image.getInterlacedDataLine(y);
//		writeLine(line);
		sendData(0x0A, line, 110);
		//complete the line
		data[0] = 0x00;
		sendData(0x0A, data, 1);
		//turn on output enable
		data[0] = 0x2F;
		sendData(0x02, data, 1);
	}
}

void Epaper::writeInvImage(EpaperImage &image) {
	//helper variables
	uint8_t data[16];
	uint8_t* dummyLine;
	for (unsigned y = 0; y < ResY; y++) {
		//set chargepump voltage level reduce voltage shift
		memset(data, 0x00, 16);
		sendData(0x04, data, 1);
		//send init again
		memset(data, 0, 16);
		data[0] = 0x00;
		data[1] = 0x00;
		data[2] = 0x00;
		data[3] = 0x7F;
		data[4] = 0xFF;
		data[5] = 0xFE;
		data[6] = 0x00;
		data[7] = 0x00;
		sendData(0x0A, data, 8);
		dummyLine = image.getInvInterlacedDataLine(y);
//		writeLine(dummyLine);
		sendData(0x0A, dummyLine, 110);
		//complete the line
		data[0] = 0x00;
		sendData(0x0A, data, 1);
		//turn on output enable
		data[0] = 0x2F;
		sendData(0x02, data, 1);
	}
}

//defined page 29
void Epaper::powerOff() {
	//helper variables
	uint8_t dummyLine[110];
	memset(dummyLine, 0x55, 110);
	for (unsigned i = 33; i < 77; i++) {
		//set the scanlines to be 0x00
		dummyLine[i] = 0x00;
	}
	uint8_t data[16];

	EpaperImage nothing;
	nothing.fill(Px_NC);
	writeImage(nothing);
//	writeLine(dummyLine);
	sendData(0x0A, dummyLine, 110);
	delay(25);
	//we do not use a border so skip this:
	//border = 0
//	delayMicroseconds(300000);//between 200 & 300 ms
	//border = 1

	//Latch reset turn on
	memset(data, 0x00, 16);
	data[0] = 0x01;
	sendData(0x03, data, 1);

	//output enable off
	memset(data, 0x00, 16);
	data[0] = 0x05;
	sendData(0x02, data, 1);

	//power off chargepump vcom
	memset(data, 0x00, 16);
	data[0] = 0x0E;
	sendData(0x05, data, 1);

	//power off chargepump negative voltage
	memset(data, 0x00, 16);
	data[0] = 0x02;
	sendData(0x05, data, 1);

	//discharge
	memset(data, 0x00, 16);
	data[0] = 0x0C;
	sendData(0x02, data, 1);

	//wait for it for 120ms
	delay(120);

	//power off all chargepumps
	memset(data, 0x00, 16);
	sendData(0x05, data, 1);

	//turn off OSC
	memset(data, 0x00, 16);
	data[0] = 0x0D;
	sendData(0x07, data, 1);

	//discharge internal
	memset(data, 0x00, 16);
	data[0] = 0x50;
	sendData(0x04, data, 1);

	//wait for it for 40ms
	delay(40);

	//discharge internal
	memset(data, 0x00, 16);
	data[0] = 0xA0;
	sendData(0x04, data, 1);

	//wait for it for 40ms
	delay(40);

	//discharge internal
	memset(data, 0x00, 16);
	sendData(0x04, data, 1);

	//make sure we meet start conditions
	digitalWrite(mENPin, LOW);
	digitalWrite(mRSTPin, LOW);
	digitalWrite(mCSPin, LOW);
	digitalWrite(mENPin, LOW);
	digitalWrite(mDCPin, HIGH);
	//wait for it for 150ms
	delay(150);
	digitalWrite(mDCPin, LOW);

}

//double Epaper::getTempCompensation() {
//	//TODO:
//	return 1;
//}

//defined page 28
void Epaper::updateImage(EpaperImage &newImage, bool skipfirst) {
	if (!mRunning) {
		return;
	}
	memcpy(&mNewImage, &newImage, sizeof(EpaperImage));

	std::cout << "powering on" << std::endl;
	powerOn();
	std::cout << "starting COG Driver" << std::endl;
	initCOGDriver();
	//TODO: when is this used?
//	double stagetime = getTempCompensation() * 630;//in [ms]

	unsigned startTime = millis();
	std::cout << "starting update at " << startTime << std::endl;

	if (!skipfirst) {
		std::cout << "stage 1" << std::endl;
		writeInvImage(mOldImage);
		for (unsigned x = 0; x < ResX; x++) {
			for (unsigned y = 0; y < ResY; y++) {
				uint8_t pixel = mOldImage.getPixel(x,y);
				if (pixel == Px_Black || pixel == Px_NC) {
					mWhiteImage.setPixel(x,y,Px_NC);
				}
				if (pixel == Px_White) {
					mWhiteImage.setPixel(x,y,Px_White);
				}
			}
		}
		std::cout << "stage 2" << std::endl;
		writeImage(mWhiteImage);
	}
	std::cout << "stage 3" << std::endl;
	writeInvImage(mNewImage);
	std::cout << "stage 4" << std::endl;
	writeImage(mNewImage);
//	writeImage(mNewImage);//optional!

	unsigned stopTime = millis();
	std::cout << "stopping update at " << stopTime << " duration: " << stopTime - startTime << std::endl;

	memcpy(&mOldImage, &mNewImage, sizeof(EpaperImage));

	std::cout << "powering off" << std::endl;
	powerOff();
}
