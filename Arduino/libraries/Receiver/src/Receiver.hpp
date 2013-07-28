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
	//data storage
	int* mValues;

public:
	Receiver (unsigned channelNum);
	virtual ~Receiver ();

	void setup(int interrupt = 0);
	int getValue(unsigned channel);
};

#endif /* RECEIVER_HPP_ */
