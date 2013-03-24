/*
 * Receiver.hpp
 *
 *  Created on: 12.01.2013
 *      Author: siddian
 */

#ifndef RECEIVER_HPP_
#define RECEIVER_HPP_

#include <Arduino.h>

class Receiver {
private:
	//how many channels do we expect
	unsigned mChannelNum;
	//do we want to normalize the values? Include double calculation...
	bool mDoNormalize;
	//data storage
	int* mValues;
//	double* mValuesNormalized;
//	//values used for normalizing
//	//these are arrays of mChannelNum values each
//	int* mBias;
//	int* mScalefactor;
public:
	Receiver (unsigned channelNum, bool doNormalize = true);
	virtual ~Receiver ();

	void setup();
	int getValue(unsigned channel);
//	double getValueNormalized(unsigned channel);
//
//	void setScaling(unsigned channel, int scaling);
//	void setBias(unsigned channel, int bias);
};

#endif /* RECEIVER_HPP_ */
