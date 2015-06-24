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

#include "Arduino.h"
#include "dsp7s04.h"

/*Pulses LATCH pin*/
void dsp7s04class::pulseLAT() {
	digitalWrite(_LAT, HIGH);
	digitalWrite(_LAT, LOW);
}

/*Prints out the _SEND block to display*/
void dsp7s04class::print() {
	shiftOut(_MOSI, _CLK, MSBFIRST, _SEND[0]);
	shiftOut(_MOSI, _CLK, MSBFIRST, _SEND[1]);
	shiftOut(_MOSI, _CLK, MSBFIRST, _SEND[2]);
	shiftOut(_MOSI, _CLK, MSBFIRST, _SEND[3]);
}

void dsp7s04class::init(int CLK, int MOSI, int LAT, int PWM) {
	_LAT = LAT;
	_CLK = CLK;
	_MOSI = MOSI;
	_PWM = PWM;

	pinMode(_CLK, OUTPUT);
	pinMode(_MOSI, OUTPUT);
	pinMode(_LAT, OUTPUT);
	pinMode(_PWM, OUTPUT);
	digitalWrite(_LAT, LOW);
}

/*
Turn on DOT segment
	int pos: indicates which DOT to turn on
*/
void dsp7s04class::setDot(int pos) {
	_SEND[pos] = _SEND[pos] | CMD_DOT;
	print();
	pulseLAT();
}

/*
Turn off DOT segment
	int pos: indicates which DOT to turn off
*/
void dsp7s04class::clearDot(int pos) {
	_SEND[pos] = _SEND[pos] & 0x7F;
	print();
	pulseLAT();
}

/*
Writes character into the position indicated. Default operation simply writes the number into the appropriate digit, all other digits display the data previously sent
	char data: the numeral character to be displayed
	int pos: indicates which digit to print the data to
*/
void dsp7s04class::write(char data, int pos) {	
	for (int i = 0; i < 4; i++){
		if (i == pos){
			_SEND[pos] = _7seg[data - '0'];
		}
		//The following commented lines are responsible for clearing all digits except the one specified. 
		//else {
		//	_SEND[i] = 0x00;
		//}
	}
	print();
	pulseLAT();
}

/*
Writes 4-digit integer onto the display
	int data: the 4-digit number to be displayed
*/
void dsp7s04class::write(int data){
	_SEND[0] = _7seg[data % 10];
	data /= 10;
	_SEND[1] = _7seg[data % 10];
	data /= 10;
	_SEND[2] = _7seg[data % 10];
	data /= 10;
	_SEND[3] = _7seg[data % 10];
	print();
	pulseLAT();
}

/*
Writes two 2-digit integers on display, separated by a DOT
	int data1: first 2-digit number to display. Will appear on the left-hand side
	int data2: second 2-digit number to display. Will appear on the right-hand side
*/
void dsp7s04class::write(int data1, int data2){
	_SEND[2] = _7seg[data1 % 10] | CMD_DOT;
	data1 /= 10;
	_SEND[3] = _7seg[data1 % 10];

	_SEND[0] = _7seg[data2 % 10];
	data2 /= 10;
	_SEND[1] = _7seg[data2 % 10];

	print();
	pulseLAT();
}

/*Turns all LEDs off*/
void dsp7s04class::clearAll() {
	_SEND[3] = CMD_OFF;
	_SEND[2] = CMD_OFF;
	_SEND[1] = CMD_OFF;
	_SEND[0] = CMD_OFF;
	print();
	pulseLAT();
}

/*Turns all LEDs on*/
void dsp7s04class::turnOn() {
	_SEND[3] = CMD_ON;
	_SEND[2] = CMD_ON;
	_SEND[1] = CMD_ON;
	_SEND[0] = CMD_ON;
	print();
	pulseLAT();
}

/*Change intensity of LEDs. 0 = Lowest brightness, 100 = brightest*/
void dsp7s04class::setBrightness(int level) {
	level = 100 - level;
	analogWrite(_PWM, STEP*level);
}

dsp7s04class dsp7s04;
