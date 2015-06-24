/*
Copyright (c) 2015, Embedded Adventures, www.embeddedadventures.com
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
this list of conditions and the following disclaimer.

- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.

- Neither the name of Embedded Adventures nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
THE POSSIBILITY OF SUCH DAMAGE.
Contact us at source [at] embeddedadventures.com
*/

//
// A library for accessing the DSP-7204 7 segment 4 digit display (with DP) from Embedded Adventures
//

#ifndef __dsp7s04_h
#define __dsp7s04_h

#include <inttypes.h>
#include <Arduino.h>

#define uns8 unsigned char
#define CMD_DOT 0x80
#define CMD_OFF 0x00
#define CMD_ON 0xFF
#define STEP 2.56

class dsp7s04class
{
private:
	void pulseLAT();
	void print();
	int _CLK;
	int _MOSI; 
	int _LAT;
	int _PWM;
	byte _SEND[4];


public:
	void init(int CLK, int MOSI, int LAT, int PWM);
	void write(char data, int pos);
	void write(int data);
	void write(int data1, int data2);
	void clearAll();
	void turnOn();
	void setDot(int pos);
	void clearDot(int pos);
	void setBrightness(int level);
};


extern dsp7s04class dsp7s04;

/*Table for byte values to represent 0-9 on display*/
const char _7seg[10] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x67 };


#endif

