/*
 * Epaper.cpp
 *
 *  Created on: 27.12.2012
 *      Author: siddian
 */

#include "Epaper.hpp"

#include "wiringPi.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Epaper::Epaper() {
	mRunning = true;
	//TODO: read this from a config file
	mChannel = 0;
	mFreq = 8000000;
	mPWMPin = 1;//only available hardware PWM pin!
	mENPin = 2;
	mCSPin = 3;
	mRSTPin = 4;
	mBUSYPin = 5;
	mDCPin = 6;

	if (wiringPiSPISetup (mChannel, mFreq) < 0) {
		fprintf(stderr, "SPI Setup failed: %s\n", strerror (errno));
		mRunning = false;
	}
	if (wiringPiSetup() < 0) {
		fprintf(stderr, "Wiring Setup failed: %s\n", strerror (errno));
		mRunning = false;
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
	delayMicroseconds(10);
	digitalWrite(mCSPin, LOW);
	//header
    wiringPiSPIDataRW (mChannel, msg, 1);
    //index
    msg[0] = registerIndex;
    wiringPiSPIDataRW (mChannel, msg, 1);
    //switch enable off and on again
	digitalWrite(mCSPin, HIGH);
	delayMicroseconds(10);//TODO: at least 10 us!
	digitalWrite(mCSPin, LOW);
	//second header
    msg[0] = 0x72;
    wiringPiSPIDataRW (mChannel, msg, 1);
	//now send the actual data!
//    for (unsigned i = 0; i < datasize; i++) {
//        msg[0] = data[i];
//        wiringPiSPIDataRW (mChannel, msg, 1);
//    }

    //TODO: or like this:
    wiringPiSPIDataRW (mChannel, data, datasize);

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
    delayMicroseconds(5000);
    pwmWrite(mPWMPin, 0);
    //enable the display
    digitalWrite(mENPin, HIGH);
    //let the PWm continue for additional 10ms
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delayMicroseconds(10000);
    pwmWrite(mPWMPin, 0);
    //before switching on the CS pin
    digitalWrite(mCSPin, HIGH);
    //we do not have a BORDER pin so skip this
    //digitalWrite(mBORDERPin, HIGH);
    //but enable reset
    digitalWrite(mRSTPin, HIGH);
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delayMicroseconds(5000);
    pwmWrite(mPWMPin, 0);
    //before switching it off
    digitalWrite(mRSTPin, LOW);
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delayMicroseconds(5000);
    pwmWrite(mPWMPin, 0);
    //before switching it on again
    digitalWrite(mRSTPin, HIGH);
    pwmWrite(mPWMPin, 512);
    //for at least 5ms
    delayMicroseconds(5000);
    pwmWrite(mPWMPin, 0);
}

//defined on page 19
//COG = Chip on glass
void Epaper::initCOGDriver() {
	//helper variables
	uint8_t data[16];

	//wait for chip to be switched on
	while (digitalRead(mBUSYPin) > 0) {
		delayMicroseconds(1);
	}
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
    delayMicroseconds(30000);
    pwmWrite(mPWMPin, 0);

	//start chargepump negative V
	memset(data, 0, 16);
	data[0] = 0x03;
	sendData(0x05, data, 1);

	//delay for 30ms
    delayMicroseconds(30000);

	//start chargepump vcom driver to on
	memset(data, 0, 16);
	data[0] = 0x0F;
	sendData(0x05, data, 1);

	//delay for 30ms
    delayMicroseconds(30000);

	//output enable to disable
	memset(data, 0, 16);
	data[0] = 0x24;
	sendData(0x02, data, 1);

	//from this point on the display pattern is expected
}

void Epaper::writeLine(uint8_t* data) {
	uint8_t tmpdata[16];
	for (unsigned i = 0; i < 110; i++) {
		tmpdata[0] = data[i];
		sendData(0x0A, tmpdata, 1);
		while (digitalRead(mBUSYPin) > 0) {
			delayMicroseconds(1);
		}
	}
}

void Epaper::writeImage(EpaperImage &image) {
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
		dummyLine = image.getInterlacedDataLine(y);
		writeLine(dummyLine);
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
		writeLine(dummyLine);
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

	//TODO:
//	writeImage(nothing);
	writeLine(dummyLine);
	delayMicroseconds(25000);
	//we do not us a border so skip this:
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
	delayMicroseconds(120000);

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
	delayMicroseconds(40000);

	//discharge internal
	memset(data, 0x00, 16);
	data[0] = 0xA0;
	sendData(0x04, data, 1);

	//wait for it for 40ms
	delayMicroseconds(40000);

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
	delayMicroseconds(150000);
	digitalWrite(mDCPin, LOW);

}

double Epaper::getTempCompensation() {
	//TODO:
	return 1;
}

//defined page 28
void Epaper::updateImage(EpaperImage &newImage) {
	powerOn();
	initCOGDriver();
	//TODO: when is this used?
//	double stagetime = getTempCompensation() * 630;//in [ms]

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
	writeImage(mWhiteImage);
	writeInvImage(mNewImage);
	writeImage(mNewImage);
//	writeImage(mNewImage);//optional!
	powerOff();
}
