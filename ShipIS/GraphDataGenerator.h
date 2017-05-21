#pragma once
#include "NeuralNetwork/NeuralNetworkHelper.h"
#include "NeuralNetwork/IceThicknessGenerator.h"
#include "NeuralNetwork/InputParams.h"
#include "NeuralNetwork/MathVelocityCalculator.h"
#include "NeuralNetwork/NeuronNetworkFactory.h"

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
	List<double>^ GetIceThickness()
	{
		return %m_IceThicknessData;
	}
	List<double>^ GetMathVelocity()
	{
		return %m_MathVelocityData;
	}
	List<double>^ GetNeuralVelocity()
	{
		return %m_NeuralVelocityData;
	}
	NeuralNetwork* GetNeuralNetwork()
	{
		return m_NeuralNetwork;
	}

private:
	InputParams* m_Params;
	IceThicknessGenerator* m_Generator;
	NeuralNetwork* m_NeuralNetwork;
	List<double> m_IceThicknessData;
	List<double> m_MathVelocityData;
	List<double> m_NeuralVelocityData;
};
}