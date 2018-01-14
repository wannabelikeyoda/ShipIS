#ifndef INPUT_PARAMS_H 
#define INPUT_PARAMS_H 

struct InputParams
{
	double max_ice_thick;
	double average_ice_thick;
	double max_snow_thick;
	double max_velocity;
	int interval;
	InputParams() {}
	InputParams(const double& _max_ice_thick, const double& _average_ice_thick, const double& _max_snow_thick, const double& _max_velocity, const int& _interval)
		: max_ice_thick(_max_ice_thick), average_ice_thick(_average_ice_thick), max_snow_thick(_max_snow_thick), max_velocity(_max_velocity), interval(_interval)
	{}
};

#endif //INPUT_PARAMS_H
