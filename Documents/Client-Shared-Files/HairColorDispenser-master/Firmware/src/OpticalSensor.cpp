#include "OpticalSensor.hpp"
#include "Pinout.h"
#include "Config.h"

OpticalSensor::OpticalSensor()
{
    pinMode(OPTICAL_SENSOR_DIODE_PIN, OUTPUT);
}

OpticalSensor::~OpticalSensor()
{

}

bool OpticalSensor::IsInZeroPosition()
{
    uint16_t sensorValue = analogRead(OPTICAL_SENSOR_PIN);

    if (sensorValue > OPTICAL_SENSOR_TRESHOLD)
        return true;

    return false;
    
}

void OpticalSensor::TurnOnOff(bool isOn)
{
    digitalWrite(OPTICAL_SENSOR_DIODE_PIN, isOn);
}