/*
 * EpaperImage.cpp
 *
 *  Created on: 27.12.2012
 *      Author: siddian
 */

#include "EpaperImage.hpp"
#include <iostream>
#include <stddef.h>
#include <string.h>

EpaperImage::EpaperImage() {
	memset(mImageData, Px_White, ResX*ResY);
	memset(mInvImageData, Px_Black, ResX*ResY);
}

EpaperImage::~EpaperImage() {

}

uint8_t* EpaperImage::getScanLineData(uint32_t y) {
	//returns the scane line for defined line y
	if (y >= ResY) {
		y = ResY-1;
	}
	memset (mScanLine, 0, 44);
	unsigned correctbyte = y / 4;

	mScanLine[correctbyte] = 0 | (192 >> ((y % 4)*2));

	return mScanLine;
}

uint8_t* EpaperImage::getEvenLineData(uint32_t y) {
	if (y >= ResY) {
		y = ResY-1;
	}

	memset(mEvenData, 0x00, 33);
	unsigned i = 0;
	for (int x = ResX-1; x > 0; x = x-8) {
//		std::cout << "x: " << x << " i: " << i << std::endl;
		mEvenData[i] = mImageData[y][x] << 6;
		mEvenData[i] |= mImageData[y][x-2] << 4;
		mEvenData[i] |= mImageData[y][x-4] << 2;
		mEvenData[i] |= mImageData[y][x-6];
		i++;
	}
	return mEvenData;
}

uint8_t* EpaperImage::getOddLineData(uint32_t y) {
	if (y >= ResY) {
		y = ResY-1;
	}

	memset(mOddData, 0x00, 33);
	unsigned i = 0;
	for (int x = ResX-2; x > 0; x = x-8) {
//		std::cout << "x: " << x << " i: " << i << std::endl;
		mOddData[i] = mImageData[y][x] << 6;
		mOddData[i] |= mImageData[y][x-2] << 4;
		mOddData[i] |= mImageData[y][x-4] << 2;
		mOddData[i] |= mImageData[y][x-6];
		i++;
	}
	return mOddData;
}

uint8_t* EpaperImage::getInvEvenLineData(uint32_t y) {
	if (y >= ResY) {
		y = ResY-1;
	}

	memset(mEvenData, 0x00, 33);
	unsigned i = 0;
	for (int x = ResX-1; x > 0; x = x-8) {
//		std::cout << "x: " << x << " i: " << i << std::endl;
		mEvenData[i] = mInvImageData[y][x] << 6;
		mEvenData[i] |= mInvImageData[y][x-2] << 4;
		mEvenData[i] |= mInvImageData[y][x-4] << 2;
		mEvenData[i] |= mInvImageData[y][x-6];
		i++;
	}
	return mEvenData;
}
uint8_t* EpaperImage::getInvOddLineData(uint32_t y) {
	if (y >= ResY) {
		y = ResY-1;
	}

	memset(mOddData, 0x00, 33);
	unsigned i = 0;
	for (int x = ResX-2; x > 0; x = x-8) {
//		std::cout << "x: " << x << " i: " << i << std::endl;
		mOddData[i] = mInvImageData[y][x] << 6;
		mOddData[i] |= mInvImageData[y][x-2] << 4;
		mOddData[i] |= mInvImageData[y][x-4] << 2;
		mOddData[i] |= mInvImageData[y][x-6];
		i++;
	}
	return mOddData;
}

uint8_t* EpaperImage::getInterlacedDataLine(uint32_t y) {
	uint8_t* evenData = getEvenLineData(y);
	uint8_t* scanline = getScanLineData(y);
	uint8_t* oddData = getOddLineData(y);

	memcpy(mInterlacedData, evenData, 33);
	for (unsigned i = 0; i < 44; i++) {
		mInterlacedData[33+i] = scanline[i];
	}
	for (unsigned i = 0; i < 33; i++) {
		mInterlacedData[33+44+i] = oddData[i];
	}

	return mInterlacedData;
}
uint8_t* EpaperImage::getInvInterlacedDataLine(uint32_t y) {
	uint8_t* evenData = getInvEvenLineData(y);
	uint8_t* scanline = getScanLineData(y);
	uint8_t* oddData = getInvOddLineData(y);

	memcpy(mInvInterlacedData, evenData, 33);
	for (unsigned i = 0; i < 44; i++) {
		mInvInterlacedData[33+i] = scanline[i];
	}
	for (unsigned i = 0; i < 33; i++) {
		mInvInterlacedData[33+44+i] = oddData[i];
	}

	return mInvInterlacedData;
}

uint8_t EpaperImage::getPixel(uint32_t x, uint32_t y) {

	if (x >= ResX) {
		x = ResX-1;
	}
	if (y >= ResY) {
		y = ResY-1;
	}
	return mImageData[y][x];
}

void EpaperImage::setPixel(uint32_t x, uint32_t y, uint8_t color) {
	uint8_t invcolor = Px_NC;
	if (color == Px_Black) {
		invcolor = Px_White;
	} else if (color == Px_White) {
		invcolor = Px_Black;
	}

	if (x >= ResX) {
		x = ResX-1;
	}
	if (y >= ResY) {
		y = ResY-1;
	}

	mImageData[y][x] = color;
	mInvImageData[y][x] = invcolor;
}
