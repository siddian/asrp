CPP	= g++
INCLUDE	= -I/usr/local/include
CPPFLAGS	= -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lwiringPi

all: e-paper

clean:
	@rm -rf *.o e-paper

EpaperImage.o: EpaperImage.cpp EpaperImage.hpp
	@$(CPP) -c $(CPPFLAGS) EpaperImage.cpp

Epaper.o: Epaper.cpp Epaper.hpp
	@$(CPP) -c $(CPPFLAGS) Epaper.cpp

e-paper.o: e-paper.cpp
	@$(CPP) -c $(CPPFLAGS) e-paper.cpp

e-paper: e-paper.o Epaper.o EpaperImage.o
	@$(CPP) -o $@ e-paper.o Epaper.o EpaperImage.o $(LDFLAGS) $(LDLIBS)
