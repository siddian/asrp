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

#ifndef PGM_H_
#define PGM_H_

/*max size of an image*/
#define MAX 800

/*
 #define LOW_VALUE 0
 #define HIGH_VALUE 255
 */


/*RGB color struct with integral types*/
typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
}RGB_INT;

struct PGMstructure
{
	int maxVal;
	int width;
	int height;
	RGB_INT data[MAX][MAX];
};

typedef struct PGMstructure PGMImage;


/***prototypes**********************************************************/
/***********************************************************************/

int getPGMfile (const char filename[], PGMImage *img);
void save(PGMImage *img);

#endif /* PGM_H_ */
