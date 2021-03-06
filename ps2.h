/*
 * ps2.h - a library to interface with ps2 devices. See comments in
 * ps2.cpp.
 * Written by Chris J. Kiick, January 2008.
 * Release into public domain.
 *   2013/1/15:upgraded to arduino 1.0 for Grove-PS/2 Adaptor
 *    by http://www.seeedstudio.com
 */

#ifndef ps2_h
#define ps2_h

//#include "WProgram.h"
#include "Arduino.h"

class PS2
{
	public:
		PS2(int clk, int data);
		void write(unsigned char data);
		unsigned char read(void);
	private:
		int _ps2clk;
		int _ps2data;
		void golo(int pin);
		void gohi(int pin);
};

#endif /* ps2_h */

