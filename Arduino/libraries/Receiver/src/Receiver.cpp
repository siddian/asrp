/*
 * Receiver.cpp
 *
 *  Created on: 12.01.2013
 *      Author: siddian
 */

#include "Receiver.hpp"

volatile unsigned channels = 0;
volatile unsigned oldtime = 0;
volatile unsigned long timepassed = 0;
volatile unsigned index = 0;
volatile int* rcValues = NULL;

void calc(void) {
	if (rcValues == NULL) {
		return;
	}
	unsigned now = micros();
	timepassed = now - oldtime;

	if (timepassed > 5000) {
		index = 0;
	} else if (timepassed > 1000) {
		rcValues[index] = timepassed;
		index++;
		index = index % channels;
	}
	oldtime = now;
}

Receiver::Receiver (unsigned channelNum, bool doNormalize) {
	mChannelNum = channelNum;
	channels = mChannelNum;
	mDoNormalize = doNormalize;

	//lets put a cap on the maximum number of channels in case someone used
	//a completely wrong number
	if (mChannelNum > 30) {
		mChannelNum = 30;
	}

	mValues = (int*)malloc(mChannelNum * sizeof(int));
	rcValues = mValues;
//	mValuesNormalized = (double*)malloc(mChannelNum * sizeof(double));
//	mBias = (int*)malloc(mChannelNum * sizeof(int));
//	mScalefactor = (int*)malloc(mChannelNum * sizeof(int));
//
//	for (unsigned i = 0; i < mChannelNum; i ++) {
//		mBias[i] = 860;
//		mScalefactor[i] = 1000;
//		mValuesNormalized = 0;
//	}

}

Receiver::~Receiver () {
	free(mValues);
//	free(mValuesNormalized);
//	free(mBias);
//	free(mScalefactor);
}

void Receiver::setup() {
	attachInterrupt(0, &calc, RISING);
}

int Receiver::getValue(unsigned channel) {
	if (channel > mChannelNum) {
		channel = mChannelNum - 1;
	}
	return mValues[channel];
}

//double Receiver::getValueNormalized(unsigned channel) {
//	if (channel > mChannelNum) {
//		channel = mChannelNum - 1;
//	}
//	return mValuesNormalized[channel];
//}
//
//void Receiver::setScaling(unsigned channel, int scaling) {
//	if (channel > mChannelNum) {
//		channel = mChannelNum - 1;
//	}
//	mScalefactor[channel] = scaling;
//}
//
//void Receiver::setBias(unsigned channel, int bias) {
//	if (channel > mChannelNum) {
//		channel = mChannelNum - 1;
//	}
//	mBias[channel] = bias;
//}
