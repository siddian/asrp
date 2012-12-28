#include <iostream>
#include "Epaper.hpp"

int main(int argc, char *argv[]) {
	EpaperImage image;
	if (argc < 2) {
		image.fillRect(50,50,100,100,Px_Black);
	} else {
		image.readFromFile(std::string(argv[1]));
	}
	Epaper display;
	display.updateImage(image, false);
	return 0;
}
