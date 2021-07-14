
#pragma once

class WeightSensorLogic  
{
	private:

	public:

		WeightSensorLogic();
		~WeightSensorLogic();

		float ReadWeightScale();
		void PrepareCalibrationOfScale(); 				// call this on empty scale
		void CalibrateScale(float knownWeightInGrams); 	// call this after putting a known weight on a scale

};