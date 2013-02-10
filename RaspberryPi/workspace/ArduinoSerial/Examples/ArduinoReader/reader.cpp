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
#include <string>
#include <errno.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <string.h>
#include <unistd.h>

int set_interface_attribs (int fd, int speed, int parity) {
	struct termios tty;
	memset (&tty, 0, sizeof tty);
	if (tcgetattr (fd, &tty) != 0)
	{
		std::cout << "error %d from tcgetattr " << errno << std::endl;
		return -1;
	}

	cfsetospeed (&tty, speed);
	cfsetispeed (&tty, speed);

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     // 8-bit chars
	// disable IGNBRK for mismatched speed tests; otherwise receive break
	// as \000 chars
	tty.c_iflag &= ~IGNBRK;         // ignore break signal
	tty.c_lflag = 0;                // no signaling chars, no echo,
	// no canonical processing
	tty.c_oflag = 0;                // no remapping, no delays
	tty.c_cc[VMIN]  = 0;            // read doesn't block
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); // shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);// ignore modem controls,
	// enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      // shut off parity
	tty.c_cflag |= parity;
	tty.c_cflag &= ~CSTOPB;
	tty.c_cflag &= ~CRTSCTS;

	if (tcsetattr (fd, TCSANOW, &tty) != 0)
	{
		std::cout << "error %d from tcsetattr" << errno << std::endl;
		return -1;
	}
	return 0;
}

void set_blocking (int fd, int should_block) {
	struct termios tty;
	memset (&tty, 0, sizeof(struct termios));
	if (tcgetattr (fd, &tty) != 0) {
		std::cout << "error %d from tggetattr" << errno <<std::endl;
		return;
	}

	tty.c_cc[VMIN]  = should_block ? 1 : 0;
	tty.c_cc[VTIME] = 5;            // 0.5 seconds read timeout

	if (tcsetattr (fd, TCSANOW, &tty) != 0) {
		std::cout << "error %d setting term attributes" << errno << std::endl;
	}
}

int main(int argc,char** argv) {

	if (argc < 2) {
		std::cout << "specify portname" << std::endl;
		return 1;
	}

	bool goon = true;
	std::string portname(argv[1]);
	int fd = open (portname.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
	if (fd < 0) {
		printf("error %d opening %s: %s", errno, portname.c_str(), strerror (errno));
		return 1;
	}

	set_interface_attribs (fd, B115200, 0);  // set speed to 115,200 bps, 8n1 (no parity)
	set_blocking (fd, 1);                // set no blocking

	char buf[1] = {0};
	int n = 1;
	while (goon) {
		memset(buf, 0, 1);
		n = read (fd, buf, 1);
		if (buf[0] == '\n') {
			std::cout << std::endl;
		} else {
			std::cout << buf[0];
		}
	}

	close(fd);
}
