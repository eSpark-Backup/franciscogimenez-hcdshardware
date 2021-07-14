#include "ProgramLogic.h"
#include "Pinout.h"
#include "Config.h"

ProgramLogic::ProgramLogic() :
    m_State(),
    m_PreviousMillis()
{
}

void ProgramLogic::Loop()
{
    // FiniteStateMachine();
}

void ProgramLogic::FiniteStateMachine()
{
    switch(m_State)
    {
    case 0:
    {
    }
    break;
    }
}
