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
#include <iostream>
#include "Epaper.hpp"

int main(int argc, char *argv[]) {
	//create container for storing the image
	EpaperImage image;
	if (argc < 2) {
		//if we have no file specified, draw a black rectangle...
		image.fillRect(50,50,100,100,Px_Black);
	} else {
		//otherwise try to read the file
		//note that an error reading the file will not alter the image
		image.readFromFile(std::string(argv[1]));
	}
	//now we have the image lets connect with the display
	Epaper display;
	//let the display handle the new image
	//we can also choose to skip the first two update steps if we want
	//by setting the second parameter to true
	display.updateImage(image, false);
	//and return
	return 0;
}
