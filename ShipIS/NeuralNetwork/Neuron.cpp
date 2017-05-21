#include "Neuron.h"

Neuron::Neuron(const INeuronStrategyPtr& strategy)
	: m_Strategy(strategy), m_Inputs(), m_ForwardNeurons()
{
	m_Bias = 0.0;
	m_Delta = 0.0;
}

void Neuron::UpdateOutput()
{
	auto net_value = m_Strategy->FindNetValue(m_Inputs, m_Bias);
	m_Output = m_Strategy->Activation(net_value);
}

void Neuron::UpdateDelta(const double & error_factor)
{
	m_Delta = m_Strategy->FindDelta(m_Output, error_factor);
}

void Neuron::UpdateFreeParams()
{
	m_Bias = m_Strategy->FindNewBias(m_Bias, m_Delta);
	m_Strategy->UpdateWeights(m_Inputs, m_Delta);
}

void Neuron::ClearParams()
{
	m_Bias = 0.0;
	m_Delta = 0.0;
	m_Strategy->RandomizeWeights(m_Inputs);
}

void Neuron::AddForwardNeuron(const INeuronPtr& neuron)
{
	m_ForwardNeurons.push_back(neuron);
}

void Neuron::AddInputNeuron(const NeuronConnection& connection)
{
	m_Inputs.push_back(connection);
}
