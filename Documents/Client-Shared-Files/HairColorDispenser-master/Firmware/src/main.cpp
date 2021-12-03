#include <Arduino.h>
#include "ProgramLogic.h"

void setup()
{
    Serial.begin(115200);
    Serial.println("Program has started");
    
    ProgramLogic m_ProgramLogic;

    while(1)
    {
        m_ProgramLogic.Loop();
    }
}

void loop() {}