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

#ifndef EPAPERIMAGE_HPP_
#define EPAPERIMAGE_HPP_

#include <stdint.h>
#include <string>

#define ResX 264//no. cols or width
#define ResY 176//no. rows or height

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

	void fillRect(uint32_t startx, uint32_t starty, uint32_t endx, uint32_t endy, uint8_t color);

	void fill(uint8_t color);

	void readFromFile(std::string name);
};

#endif /* EPAPERIMAGE_HPP_ */
