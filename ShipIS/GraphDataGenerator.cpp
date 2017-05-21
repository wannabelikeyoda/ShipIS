#include "GraphDataGenerator.h"

namespace ShipIS
{
ShipIS::GraphDataGenerator::GraphDataGenerator()
{
	m_NeuralNetwork = new NeuralNetwork( NeuronNetworkFactory::CreateNetwork( { 4,4,1 }, 0.5 ) );
}

System::Void ShipIS::GraphDataGenerator::CreateIceGenerator()
{
	m_Generator = new IceThicknessGenerator( m_Params->max_ice_thick, m_Params->average_ice_thick );
}

System::Void ShipIS::GraphDataGenerator::GenerateNext()
{
	//Ice graph
	auto curr_ice_thick = m_Generator->Next();
	m_IceThicknessData.Add( curr_ice_thick );

	//Math graph
	double math_valocity = MathVelocityCalculator::CalculateVelocitySimple( curr_ice_thick, curr_ice_thick / 3.0, *m_Params );
	m_MathVelocityData.Add( math_valocity );

	//Neural graph
	auto ice_prev_value = curr_ice_thick;
	if ( m_IceThicknessData.Count > 1 )
	{
		ice_prev_value = m_IceThicknessData[m_IceThicknessData.Count - 2];
	}
	auto snow_curr_thick = curr_ice_thick / 3.0;
	auto snow_prev_thick = ice_prev_value / 3.0;
	std::vector<double> input_data = { curr_ice_thick, snow_curr_thick, ( ice_prev_value - curr_ice_thick ) / ( m_Params->interval + 0.0 ), ( snow_prev_thick - snow_curr_thick ) / ( m_Params->interval + 0.0 ) };

	m_NeuralNetwork->RunNetwork( input_data );

	double neural_velocity = m_NeuralNetwork->GetOutputValue()[0] * m_Params->max_velocity;
	m_NeuralVelocityData.Add( neural_velocity );

	//Fuzzy
	//...
}

System::Void ShipIS::GraphDataGenerator::SetParams( InputParams * params )
{
	m_Params = params;
}

InputParams* GraphDataGenerator::GetParams()
{
	return m_Params;
}

System::Void GraphDataGenerator::DeleteOverData(int capacity)
{
	if ( m_IceThicknessData.Count - 1 > capacity )
	{
		m_IceThicknessData.RemoveAt( 0 );
	}
	if ( m_MathVelocityData.Count - 1 > capacity )
	{
		m_MathVelocityData.RemoveAt( 0 );
	}
	if ( m_NeuralVelocityData.Count - 1 > capacity )
	{
		m_NeuralVelocityData.RemoveAt( 0 );
	}
	/*
	if (m_IceThicknessData->Count - 1 > _capacity)
	{
	m_IceThicknessData.RemoveAt(0);
	}
	*/
}

}