/*
 * pgm.h
 *
 *  Created on: 28.12.2012
 *      Author: siddian
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
