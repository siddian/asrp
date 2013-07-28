/*
 * Receiver.cpp
 *
 *  Created on: 12.01.2013
 *      Author: siddian
 */

#include "Receiver.hpp"
#include <Arduino.h>

static unsigned channels = 0;
static unsigned oldtime = 0;
static unsigned long timepassed = 0;
static unsigned index = 0;
static int* rcValues = NULL;

void calc(void) {
	if (rcValues == NULL) {
		return;
	}
	unsigned now = micros();
	timepassed = now - oldtime;
	oldtime = now;

	if (timepassed > 3000) {
		index = 0;
		timepassed = 0;
	} else if (timepassed > 700 && index < channels) {
		rcValues[index] = timepassed;
		index++;
		timepassed = 0;
	}
}

Receiver::Receiver (unsigned channelNum) {
	mChannelNum = channelNum;
	channels = mChannelNum;

	//lets put a cap on the maximum number of channels in case someone used
	//a completely wrong number
	if (mChannelNum > 30) {
		mChannelNum = 30;
	}

	mValues = (int*)malloc(mChannelNum * sizeof(int));
	rcValues = mValues;
	for (unsigned i = 0; i < mChannelNum; i++) {
		rcValues[i] = 0;
	}
}

Receiver::~Receiver () {
	free(mValues);
//	free(mValuesNormalized);
//	free(mBias);
//	free(mScalefactor);
}

void Receiver::setup(int interrupt) {
//	attachInterrupt(interrupt, &calc, RISING);
	attachInterrupt(interrupt, &calc, FALLING);
}

int Receiver::getValue(unsigned channel) {
	int val = 0;
	if (channel > mChannelNum) {
		channel = mChannelNum - 1;
	}
	cli();
	val = mValues[channel];
	sei();
	return val;
}

