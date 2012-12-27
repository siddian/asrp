/*
 * Epaper.hpp
 *
 *  Created on: 27.12.2012
 *      Author: siddian
 */

#ifndef EPAPER_HPP_
#define EPAPER_HPP_

#include <stdint.h>
#include <stddef.h>
#include "EpaperImage.hpp"

class Epaper {
	//is everything ok?
	bool mRunning;
	//seems like the raspberry has two channels?
	int mChannel;
	//frequency of SPI bus
	int mFreq;
	//pin number of the CS pin
	int mCSPin;
	//pin number of Enable pin
	int mENPin;
	//pin number of Reset pin
	int mRSTPin;
	//pin of PWM signal
	int mPWMPin;
	//pin number of the BUSY pin
	int mBUSYPin;
	//pin number of the discharge pin
	int mDCPin;

	//data containers
	EpaperImage mOldImage;
	EpaperImage mNewImage;
	EpaperImage mWhiteImage;
private:
	void sendData(uint8_t registerIndex, uint8_t* data, size_t datasize);
	void powerOn();
	void initCOGDriver();
	double getTempCompensation();
	void writeLine(uint8_t* data);//expects an array of length (264+176)*2 bits = 110 bytes
	void writeImage(EpaperImage &image);
	void writeInvImage(EpaperImage &image);
	void powerOff();
public:
	Epaper();
	virtual ~Epaper();

	void updateImage(EpaperImage &newImage);
};

#endif /* EPAPER_HPP_ */