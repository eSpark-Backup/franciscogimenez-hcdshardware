#include "WeightSensorLogic.hpp"
#include "Libraries/HX711.h"
#include "Pinout.h"
#include "Config.h"
#include <EEPROM.h>

HX711 m_Scale;

WeightSensorLogic::WeightSensorLogic()
{
    float calibrationNumber = LOADCELL_CALIBRATION_NUMBER;
    EEPROM.begin(EEPROM_SIZE);
    float eepromValue = EEPROM.readFloat(LOADCELL_EEPROM_ADDRESS);
    if (eepromValue != 0.0)
        calibrationNumber = eepromValue;
    m_Scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    m_Scale.set_scale(calibrationNumber);
}

WeightSensorLogic::~WeightSensorLogic()
{

}

float WeightSensorLogic::ReadWeightScale()
{
    float weight;

    m_Scale.power_up();
    weight = m_Scale.get_units(LOADCELL_NUMBER_OF_READS);
    m_Scale.power_down();

    return weight;
}

void WeightSensorLogic::PrepareCalibrationOfScale()
{
    m_Scale.set_scale();
    m_Scale.tare();
}

void WeightSensorLogic::CalibrateScale(float knownWeightInGrams)
{
    float weight = m_Scale.get_units(10);
    float calibrationFactor = weight / knownWeightInGrams;
    m_Scale.set_scale(calibrationFactor);
    EEPROM.put(LOADCELL_EEPROM_ADDRESS, calibrationFactor);
}