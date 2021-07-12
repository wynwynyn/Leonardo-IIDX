/*
 *  Credit to lizardbeans for the original code: https://github.com/lizardbeans/diy-iidx
 *  Modified for yuancon IIDX controller
 *  Does not make use of LED pins as I am powering these externally (default Yuan LEDs are okay, but a bit dim).
 *  
 *  Default boot of Arduino puts the turntable in analogue mode. Perfect for Infinitas, etc
 *  Hold key 7 while plugging in controller to enable Digital TT mode - turntable will report xAxis left/right, then
 *  return to 0 position. Ideal for LR2.
 *  
 *  v1.1.2 - Fixed xAxis intermittently returning to 0 while still turning turntable at low speeds
 */

#include "iivx_leo.h"
#include "Encoder.h"
iivxReport_t report; 

#define REPORT_DELAY 2000
// Number of microseconds between HID reports
// 2000 = 500hz

uint8_t buttonCount = 12;
uint8_t buttonPins[] = {3,4,5,6,7,18,19,8,20,21,22,23};

// turntable stuff
bool analTT = false;
int curPosTT = 0;
int lastPosTT = 0;
int xTT;
int timerTT = 0;
bool delayRunning = false;


#define ENCODER_SENSITIVITY (double) 2.375
// encoder sensitivity = number of positions per rotation times 4 (24*4) / number of positions for HID report (256)
Encoder encL(0,1);

void setup() {
  Serial.begin(9600);
  delay(1000);
  // Setup I/O for pins
  for(int i=0;i<buttonCount;i++){
    pinMode(buttonPins[i],INPUT_PULLUP);      
  }
  if(digitalRead(buttonPins[6])!= LOW){ // hold key 7 for digi TT
    analTT = true;    
  }
}

void loop() {
  // Read buttons
  for(int i=0;i<buttonCount;i++){
    if(digitalRead(buttonPins[i])!=HIGH){
      report.buttons |= (uint16_t)1 << i;
      Serial.print(i);
    } else {
      report.buttons &= ~((uint16_t)1 << i);
    }
  }
    
  //Read Encoders
  curPosTT = (uint8_t)((int32_t)(encL.read() / ENCODER_SENSITIVITY) % 256);
  if(analTT == true){  
    report.xAxis = curPosTT;
  } else {
    if (curPosTT > lastPosTT){
        delayRunning = true;
        xTT = 127;
        lastPosTT = curPosTT;
    } else if(curPosTT < lastPosTT){
        delayRunning = true;
        xTT = -128;
        lastPosTT = curPosTT;
    } else if (delayRunning && curPosTT == lastPosTT){
        if(timerTT < 80){ // delay
          report.xAxis = xTT;
          timerTT++;
        } else {
          delayRunning = false;
          timerTT = 0;
        }
    } else {
       xTT = 0;
       timerTT = 0;
       delayRunning = false;
       report.xAxis = xTT;
    }
  }

  // Send report and delay
  iivx.setState(&report);
  delayMicroseconds(REPORT_DELAY);
}
