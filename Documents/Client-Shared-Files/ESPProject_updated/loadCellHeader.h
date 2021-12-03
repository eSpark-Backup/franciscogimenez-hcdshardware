
#include "HX711_mod.h"

// constants

const float R0 = 3746;   // reading when no mass on the load cell
const float R1 = 2983;   // reading when there is mass M1 on the cell
const float M1 = 2000;   // mass M1 in grams

const float calibrationFactor = (R1 - R0) / M1;


void initLoadCell();
float readWeight();

HX711 cell;

void initLoadCell() {
  cell.begin(dout, sck);
}


float readWeight() {  // in grams
  float aa = 0, bb = 0, cc = 0;
  for ( byte x = 0; x < 50; x++ ) {  // 200 samples
    aa += cell.read();
  }
  bb = aa / 50;
  cc = (bb - R0) / calibrationFactor;
  return cc;
}
