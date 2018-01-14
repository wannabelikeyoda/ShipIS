#include "stdafx.h"
#include "IceThicknessGenerator.h"
#include "MathVelocityCalculator.h"
#include "InputParams.h"


IceThicknessGenerator::IceThicknessGenerator( const double & max_value, const double & average_value )
{
    m_MaxValue = max_value;
    m_AverageValue = average_value;
    m_CurrentValue = m_AverageValue;
}

double IceThicknessGenerator::Next()
{
    double generated_noise = ( std::rand() % 400 / 100.0 - 2 ) / 10.0;
    double deviation = ( m_CurrentValue - m_AverageValue ) / m_AverageValue;
    double candidat = m_CurrentValue;
    if ( ( deviation < 0 && generated_noise < 0 ) || ( deviation > 0 && generated_noise > 0 ) )
    {
        candidat += ( 1 - std::abs( deviation ) )*generated_noise;
    }
    else
    {
        candidat += ( 1 + std::abs( deviation ) )*generated_noise;
    }

    if ( candidat > m_MaxValue )
        candidat = m_MaxValue;
    m_CurrentValue = candidat;
    return m_CurrentValue;
}

GeneratorTrainingForIceThickness::GeneratorTrainingForIceThickness( const IceThicknessGeneratorPtr& generator, InputParams& params )
    : m_IceThicknessGenerator( generator ), m_Params( params )
{}

neural::TTrainingDataVector GeneratorTrainingForIceThickness::GenerateTrainingVector( const int& count )
{
    std::vector<double> ice_thickness_vector;
    std::vector<double> snow_thickness_vector;
    std::vector<double> delta_ice_thickness_vector;
    std::vector<double> delta_snow_thickness_vector;
    std::vector<double> velocity_vector;
    for ( int i = 0; i < count; i++ )
    {
        double ice_prev_value = 0;
        double snow_prev_value = 0;
        if ( ice_thickness_vector.size() != 0 && snow_thickness_vector.size() != 0 )
        {
            ice_prev_value = ice_thickness_vector.back();
            snow_prev_value = snow_thickness_vector.back();
        }
        ice_thickness_vector.push_back( m_IceThicknessGenerator->Next() );
        snow_thickness_vector.push_back( ice_thickness_vector.back() / 3.0 ); // thickness of snow = (ice / 3)
        delta_ice_thickness_vector.push_back( ( ice_prev_value - ice_thickness_vector.back() ) / ( m_Params.interval + 0.0 ) );
        delta_snow_thickness_vector.push_back( ( snow_prev_value - snow_thickness_vector.back() ) / ( m_Params.interval + 0.0 ) );

        velocity_vector.push_back( MathVelocityCalculator::CalculateVelocitySimple( ice_thickness_vector.back(), snow_thickness_vector.back(), m_Params ) / m_Params.max_velocity );
    }
    return neural::TrainingDataVectorFactory::GenerateTrainingDataVector4( ice_thickness_vector,
        snow_thickness_vector,
        delta_ice_thickness_vector,
        delta_snow_thickness_vector,
        velocity_vector );
}
