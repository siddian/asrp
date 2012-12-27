#include <iostream>
#include "Epaper.hpp"

int main() {
	EpaperImage image;
	image.setPixel(10,10,Px_Black);

	Epaper display;
	display.updateImage(image);
	return 0;
}
