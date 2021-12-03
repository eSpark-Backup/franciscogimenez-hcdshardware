
#pragma once

#include "Arduino.h"

class OpticalSensor  
{
	private:

	public:

		OpticalSensor();
		~OpticalSensor();

		bool IsInZeroPosition();
		void TurnOnOff(bool isOn = false);

};