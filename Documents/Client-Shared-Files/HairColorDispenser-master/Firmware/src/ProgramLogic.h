#ifndef PROGRAMLOGIC_H
#define PROGRAMLOGIC_H

#include "Arduino.h"

const int WAITING_FOR_NEW_WEIGHT            =  0;
const int WAITING_FOR_STABLE_MEASUREMENT    =  1;
const int NEW_WEIGHT_PRESENT                =  2;
const int WAITING_FOR_PLATE_REMOVAL         =  3;

const long      m_StableMeasurementInterval = 1000;

class ProgramLogic
{
public:
    ProgramLogic();

    void Loop();

private:
    void FiniteStateMachine();

    int m_State;
    unsigned long m_PreviousMillis;
};

#endif // PROGRAMLOGIC_H