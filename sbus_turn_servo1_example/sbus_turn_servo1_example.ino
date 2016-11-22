#include "SBUS.h"

// a SBUS object, which is on Teensy hardware
// serial port 1
SBUS sbusOut(1);

// channel, fail safe, and lost frames data
uint16_t channels[16];
uint8_t failSafe;
uint16_t lostFrames = 0;
uint16_t direction = 10;

unsigned long previousMillis = 0;        // will store last time S.BUS was updated
const long INTERVAL = 7;           // interval at which to update S.BUS (milliseconds)
const uint16_t SBUS_VALUE_MIN = 0x0; // min value
const uint16_t SBUS_VALUE_MAX = 0x7FF; // max value / 11 Bit per channel

void setup() {
  // begin the SBUS communication
  sbusOut.begin();

  for( int i=0; i<16; i++ ) {
     channels[i]=0x0001;  
  }
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= INTERVAL) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    channels[0]+=direction;
    if( channels[0] < 5 || channels[0] >= SBUS_VALUE_MAX ) {
      direction*=-1;  
    }
    
    // write the SBUS packet to an SBUS compatible servo
    sbusOut.write(&channels[0]);
  }
}
