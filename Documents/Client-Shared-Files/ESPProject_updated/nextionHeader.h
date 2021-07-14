// functions protoypes

void  initNextion();
void  nextionLoop();
void screen_update();

void reset_button_release(void *ptr);
void mute_button_release(void *ptr);

// libraries
#include "Nextion.h"

void  initNextion() {
  nexInit(NEXTION_BAUD); 
}

void nextionLoop() {
  
}
