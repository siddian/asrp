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
	inline void sendData(uint8_t registerIndex, uint8_t* data, size_t datasize);
	void powerOn();
	void initCOGDriver();
//	double getTempCompensation();
	void writeImage(EpaperImage &image);
	void writeInvImage(EpaperImage &image);
	void powerOff();
public:
	Epaper();
	virtual ~Epaper();
	/*
	 * writes a new image to the display following this execution process:
	 * 1. Power On
	 * 2. Initialize COG (Circuit on Glass) Driver
	 * 3. Stage 1 Display update (writing inverted old image)
	 * 4. Stage 2 Display update (writing a white image)
	 * 5. Stage 3 Display update (writing inverted new image)
	 * 6. Stage 4 Display update (writing new image)
	 * 7. Power Off
	 *
	 * By specifying skipfirst = true the points 3.&4. are skipped from the update process.
	 */
	void updateImage(EpaperImage &newImage, bool skipfirst = false);
};

#endif /* EPAPER_HPP_ */
