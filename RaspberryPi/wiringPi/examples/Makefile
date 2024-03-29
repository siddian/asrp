#
# Makefile:
#	wiringPi - Wiring Compatable library for the Raspberry Pi
#	https://projects.drogon.net/wiring-pi
#
#	Copyright (c) 2012 Gordon Henderson
#################################################################################
# This file is part of wiringPi:
#	Wiring Compatable library for the Raspberry Pi
#
#    wiringPi is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    wiringPi is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with wiringPi.  If not, see <http://www.gnu.org/licenses/>.
#################################################################################


#DEBUG	= -g -O0
DEBUG	= -O3
CC	= gcc
INCLUDE	= -I/usr/local/include
CFLAGS	= $(DEBUG) -Wall $(INCLUDE) -Winline -pipe

LDFLAGS	= -L/usr/local/lib
LDLIBS    = -lwiringPi

# Should not alter anything below this line
###############################################################################

SRC	=	test1.c test2.c speed.c lcd.c wfi.c		\
		piface.c gertboard.c nes.c			\
		pwm.c tone.c servo.c				\
		delayTest.c serialRead.c okLed.c		\
		spi.c switch.c

OBJ	=	$(SRC:.c=.o)

BINS	=	$(SRC:.c=)

all:	
	@cat README.TXT
	@echo "    $(BINS)" | fmt
	@echo ""

test1:	test1.o
	@echo [link]
	@$(CC) -o $@ test1.o $(LDFLAGS) $(LDLIBS)
	
test2:	test2.o
	@echo [link]
	@$(CC) -o $@ test2.o $(LDFLAGS) $(LDLIBS)

speed:	speed.o
	@echo [link]
	@$(CC) -o $@ speed.o $(LDFLAGS) $(LDLIBS)

lcd:	lcd.o
	@echo [link]
	@$(CC) -o $@ lcd.o $(LDFLAGS) $(LDLIBS)

wfi:	wfi.o
	@echo [link]
	@$(CC) -o $@ wfi.o $(LDFLAGS) $(LDLIBS)

piface:	piface.o
	@echo [link]
	@$(CC) -o $@ piface.o $(LDFLAGS) $(LDLIBS) -lpthread

gertboard:	gertboard.o
	@echo [link]
	@$(CC) -o $@ gertboard.o $(LDFLAGS) $(LDLIBS) -lm

nes:	nes.o
	@echo [link]
	@$(CC) -o $@ nes.o $(LDFLAGS) $(LDLIBS) -lm

pwm:	pwm.o
	@echo [link]
	@$(CC) -o $@ pwm.o $(LDFLAGS) $(LDLIBS) -lm -lpthread

delayTest:	delayTest.o
	@echo [link]
	@$(CC) -o $@ delayTest.o $(LDFLAGS) $(LDLIBS)

serialRead:	serialRead.o
	@echo [link]
	@$(CC) -o $@ serialRead.o $(LDFLAGS) $(LDLIBS)

okLed:	okLed.o
	@echo [link]
	@$(CC) -o $@ okLed.o $(LDFLAGS) $(LDLIBS)

tone:	tone.o
	@echo [link]
	@$(CC) -o $@ tone.o $(LDFLAGS) $(LDLIBS)

servo:	servo.o
	@echo [link]
	@$(CC) -o $@ servo.o $(LDFLAGS) $(LDLIBS)

spi:	spi.o
	@echo [link]
	@$(CC) -o $@ spi.o $(LDFLAGS) $(LDLIBS)

switch:	switch.o
	@echo [link]
	@$(CC) -o $@ switch.o $(LDFLAGS) $(LDLIBS)

.c.o:
	@echo [CC] $<
	@$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJ) *~ core tags $(BINS)

tags:	$(SRC)
	@echo [ctags]
	@ctags $(SRC)

depend:
	makedepend -Y $(SRC)

# DO NOT DELETE
