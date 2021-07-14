
#pragma once

struct Color
{
	int red;
	int green;
	int blue;
};

class RgbLedLogic  
{
	private:

	public:

		RgbLedLogic();
		~RgbLedLogic();

		void SetDiodeColor(int diode, Color color);
		void TurnOffAllLeds();

};