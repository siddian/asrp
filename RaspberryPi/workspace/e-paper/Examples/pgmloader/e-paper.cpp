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
