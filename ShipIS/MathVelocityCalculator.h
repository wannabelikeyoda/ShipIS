#pragma once

struct InputParams;

class MathVelocityCalculator
{
public:
    static double CalculateVelocitySimple( const double& ice_thick, const double& snow_thick, const InputParams& params );
};
