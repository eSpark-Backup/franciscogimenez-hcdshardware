#include "FIrePinLogic.hpp"
#include "Servo.h"
#include "Pinout.h"
#include "Config.h"

Servo m_FirePinServo;

FIrePinLogic::FIrePinLogic()
{
    m_FirePinServo.attach(FIRE_PIN);
}

FIrePinLogic::~FIrePinLogic()
{

}

void ActivateFirePin()
{
    m_FirePinServo.write(SERVO_FIRE_PIN_MAX);
}

void RetractFirePin()
{
    m_FirePinServo.write(SERVO_FIRE_PIN_MIN);
}

void CustomPosition(int position)
{
    m_FirePinServo.write(position);
}