/*
Copyright (c) 2015, Embedded Adventures
All rights reserved.
Contact us at source [at] embeddedadventures.com
www.embeddedadventures.com
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
*/

//DSP7S04 7-Segment display demo
//Written originally by Embedded Adventures

#include <dsp7s04.h>

/*pin configurations for this demo*/
#define CLK 12
#define MOSI 11
#define LAT 5
#define PW 6

void setup() {
  dsp7s04.init(CLK, MOSI, LAT, PW);
  Serial.begin(115200);
  Serial.println("Initializing...");
}

void loop() {
  demoBrightness();
  dsp7s04.clearAll();
  demoDots();
  demoNumbers();
}

void demoNumbers() {
  Serial.println("Run through 0-9 on all digits");
  for (int i = 0; i < 10; i++){
    int demoInt = i*1000 + i*100 + i*10 + i;
    demoInt = i*1000 + i*100 + i*10 + i;
    dsp7s04.write(demoInt);
    delay(500);
    dsp7s04.clearAll();
    delay(500);
  }
  Serial.println("Second form of write(), using two ints");
  dsp7s04.write(20, 15);
  delay(500);
  dsp7s04.clearAll();
  Serial.println("Third form of write(), specifiying a digit and a number to write as a char");
  dsp7s04.write('1', 3);
  delay(500);
  dsp7s04.write('3', 2);
  delay(500);
  dsp7s04.write('5', 1);
  delay(500);
  dsp7s04.write('7', 0);
  delay(500);
  dsp7s04.clearAll();  
}

void demoDots() {
  Serial.println("Demo of dots");
  for (int i = 3; i >= 0; i--){
    if (i != 3) {
      dsp7s04.clearDot(i+1);
    }
    dsp7s04.setDot(i);
    delay(500);
  }
   Serial.println("Blinking all dots");
   for (int i = 3; i >= 0; i--){
    dsp7s04.setDot(0);
    dsp7s04.setDot(1);
    dsp7s04.setDot(2);
    dsp7s04.setDot(3);
    delay(500);
    dsp7s04.clearAll();
    delay(500);
  }
}

void demoBrightness() {
  dsp7s04.turnOn();
  dsp7s04.setBrightness(0);
  Serial.println("Setting brightness level at 100%");
  delay(1000);
  dsp7s04.setBrightness(75);
  Serial.println("Setting brightness level at 75%");
  delay(1000);
  dsp7s04.setBrightness(50);
  Serial.println("Setting brightness level at 50%");
  delay(1000);
  dsp7s04.setBrightness(25);
  Serial.println("Setting brightness level at 25%");
  delay(1000);
  dsp7s04.setBrightness(0);
  Serial.println("Setting brightness level at 0%");
  delay(1000);
  
  for (int i = 10; i < 100; i+=10){
    dsp7s04.setBrightness(i);
    delay(500);
  }
}
