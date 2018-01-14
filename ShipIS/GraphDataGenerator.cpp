#include "GraphDataGenerator.h"
#include "FuzzyModel/RulesBase.h"

namespace ShipIS
{
ShipIS::GraphDataGenerator::GraphDataGenerator()
{
	m_NeuralNetwork = new NeuralNetwork( NeuronNetworkFactory::CreateNetwork( { 4,4,1 }, 0.5 ) );
	m_Mamdani = new fuzzy::MamdaniAlgorithm( 2, 1 );
	m_IceThicknessData = gcnew List<double>(30);
	m_MathVelocityData = gcnew List<double>( 30 );
	m_NeuralVelocityData = gcnew List<double>( 30 );
	m_FuzzyVelocityData = gcnew List<double>( 30 );
	m_PreferVelocityData = gcnew List<double>( 30 );
}

System::Void GraphDataGenerator::CreateIceGenerator()
{
	m_Generator = new IceThicknessGenerator( m_Params->max_ice_thick, m_Params->average_ice_thick );
}

System::Void GraphDataGenerator::GenerateNext()
{
	//Ice graph
	auto curr_ice_thick = m_Generator->Next();
	m_IceThicknessData->Add( curr_ice_thick );

	//Math graph
	double math_valocity = MathVelocityCalculator::CalculateVelocitySimple( curr_ice_thick, curr_ice_thick / 3.0, *m_Params );
	m_MathVelocityData->Add( math_valocity );

	//Neural graph
	auto ice_prev_value = curr_ice_thick;
	if ( m_IceThicknessData->Count > 1 )
	{
		ice_prev_value = m_IceThicknessData[m_IceThicknessData->Count - 2];
	}
	auto snow_curr_thick = curr_ice_thick / 3.0;
	auto snow_prev_thick = ice_prev_value / 3.0;
	std::vector<double> input_data = { curr_ice_thick, snow_curr_thick, ( ice_prev_value - curr_ice_thick ) / ( m_Params->interval + 0.0 ), ( snow_prev_thick - snow_curr_thick ) / ( m_Params->interval + 0.0 ) };

	m_NeuralNetwork->RunNetwork( input_data );

	double neural_velocity = m_NeuralNetwork->GetOutputValue()[0] * m_Params->max_velocity;
	m_NeuralVelocityData->Add( neural_velocity );

	//Fuzzy
	std::vector<double> input_data_for_fuzzy = { input_data[0], input_data[1] };
	double fuzzy_velocity = (m_Mamdani->Execute( input_data_for_fuzzy ))[0];
	m_FuzzyVelocityData->Add( fuzzy_velocity );

	//Prefer model
	auto delta_velocity_neural = math_valocity - neural_velocity;
	auto delta_velocity_fuzzy = math_valocity - fuzzy_velocity;
	auto allowable_delta = math_valocity*0.05;
	if ( std::abs(delta_velocity_neural) <= allowable_delta )
		m_PreferVelocityData->Add( neural_velocity );
	else if ( std::abs( delta_velocity_fuzzy) <= allowable_delta )
		m_PreferVelocityData->Add( fuzzy_velocity );
	else
		m_PreferVelocityData->Add( math_valocity );
}

System::Void GraphDataGenerator::SetParams( InputParams * params )
{
	m_Params = params;
}

InputParams* GraphDataGenerator::GetParams()
{
	return m_Params;
}

fuzzy::MamdaniAlgorithm* GraphDataGenerator::GetFuzzyAlgorithm()
{
	return m_Mamdani;
}

System::Void GraphDataGenerator::DeleteOverData( int capacity )
{
	if ( m_IceThicknessData->Count - 1 > capacity )
	{
		m_IceThicknessData->RemoveAt( 0 );
	}
	if ( m_MathVelocityData->Count - 1 > capacity )
	{
		m_MathVelocityData->RemoveAt( 0 );
	}
	if ( m_NeuralVelocityData->Count - 1 > capacity )
	{
		m_NeuralVelocityData->RemoveAt( 0 );
	}
	if ( m_FuzzyVelocityData->Count - 1 > capacity )
	{
		m_FuzzyVelocityData->RemoveAt( 0 );
	}
	if ( m_PreferVelocityData->Count - 1 > capacity )
	{
		m_PreferVelocityData->RemoveAt( 0 );
	}
}

}