#pragma once
#include "InputParams.h"

class MathVelocityCalculator
{
public:
	static double CalculateVelocitySimple(const double& ice_thick, const double& snow_thick, const InputParams& params)
	{
		double ice_deviation = ice_thick / params.max_ice_thick;
		double snow_deviation = snow_thick / params.max_snow_thick;
		return params.max_velocity*(1.0 - 0.3*ice_deviation - 0.25*ice_deviation*ice_deviation - 0.2*snow_deviation - 0.2*snow_deviation*snow_deviation);
	}
};
