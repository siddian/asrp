/*
 * EpaperImage.hpp
 *
 *  Created on: 27.12.2012
 *      Author: siddian
 */

#ifndef EPAPERIMAGE_HPP_
#define EPAPERIMAGE_HPP_

#include <stdint.h>

#define ResX 264
#define ResY 176

#define Px_Black 3
#define Px_White 2
#define Px_NC 1

class EpaperImage {
	uint8_t mImageData[ResY][ResX];
	uint8_t mInvImageData[ResY][ResX];

	//helper data
	uint8_t mScanLine[44];

	uint8_t mEvenData[33];
	uint8_t mOddData[33];

	uint8_t mInvEvenData[33];
	uint8_t mInvOddData[33];

	uint8_t mInterlacedData[110];
	uint8_t mInvInterlacedData[110];
public://for debbugging temporarily public
//private:
	uint8_t* getScanLineData(uint32_t y);
	uint8_t* getEvenLineData(uint32_t y);
	uint8_t* getOddLineData(uint32_t y);

	uint8_t* getInvEvenLineData(uint32_t y);
	uint8_t* getInvOddLineData(uint32_t y);
public:
	EpaperImage();
	virtual ~EpaperImage();

	uint8_t* getInterlacedDataLine(uint32_t y);
	uint8_t* getInvInterlacedDataLine(uint32_t y);

	uint8_t getPixel(uint32_t x, uint32_t y);
	void setPixel(uint32_t x, uint32_t y, uint8_t color);

};

#endif /* EPAPERIMAGE_HPP_ */
