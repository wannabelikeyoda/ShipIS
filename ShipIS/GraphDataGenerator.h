#pragma once

#include "FuzzyModel/MamdaniAlgorithm.h"
#include "NeuralNetwork/NeuralNetwork.h"

struct InputParams;
class IceThicknessGenerator;

namespace ShipIS
{
using namespace System::Collections::Generic;

ref class GraphDataGenerator
{
public:
	GraphDataGenerator();
	System::Void CreateIceGenerator();
	System::Void GenerateNext();
	System::Void DeleteOverData( int capacity );

	System::Void SetParams( InputParams* params );
	InputParams* GetParams();
	fuzzy::MamdaniAlgorithm* GetFuzzyAlgorithm();
	List<double>^ GetIceThickness()
	{
		return m_IceThicknessData;
	}
	List<double>^ GetMathVelocity()
	{
		return m_MathVelocityData;
	}
	List<double>^ GetNeuralVelocity()
	{
		return m_NeuralVelocityData;
	}
	List<double>^ GetFuzzyVelocity()
	{
		return m_FuzzyVelocityData;
	}
	List<double>^ GetPreferVelocity()
	{
		return m_PreferVelocityData;
	}
    neural::NeuralNetwork* GetNeuralNetwork()
	{
		return m_NeuralNetwork;
	}

private:
	InputParams* m_Params;
	IceThicknessGenerator* m_Generator;
	fuzzy::MamdaniAlgorithm* m_Mamdani;
    neural::NeuralNetwork* m_NeuralNetwork;
	List<double>^ m_IceThicknessData;
	List<double>^ m_MathVelocityData;
	List<double>^ m_NeuralVelocityData;
	List<double>^ m_FuzzyVelocityData;
	List<double>^ m_PreferVelocityData;
};
}