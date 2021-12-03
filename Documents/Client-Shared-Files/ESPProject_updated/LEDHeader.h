
#include "Adafruit_NeoPixel_mod.h"

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel myLED = Adafruit_NeoPixel(ledNum, addressableLED, NEO_GRB + NEO_KHZ800);

void initLED();
void shine();

void initLED() {
  myLED.begin();
}


void shine() {
  for ( byte x = 0; x <= ledNum; x++ ) {
    myLED.setPixelColor(x, myLED.Color(255, 255, 255));
    myLED.show();
  }
}
