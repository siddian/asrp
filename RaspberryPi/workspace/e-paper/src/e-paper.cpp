#include <iostream>
#include "Epaper.hpp"

int main() {
	EpaperImage image;
	image.fillRect(50,50,100,100,Px_Black);
	Epaper display;
	display.updateImage(image);
	return 0;
}
