#include "../stdafx.h"
#include "BackPropNeuronStrategy.h"

BackPropNeuronStrategy::BackPropNeuronStrategy(const double & learning_rate)
	: m_LearningRate(learning_rate)
{}

double BackPropNeuronStrategy::FindDelta(const double & output, const double & error_factor)
{
	return output * (1-output) * error_factor;
}

double BackPropNeuronStrategy::Activation(const double & value)
{
	return 1 / (1 + exp(- value));
	//return (exp(2 * value)-1) / (1+exp(2*value));
}

double BackPropNeuronStrategy::FindNetValue(const TNeuronConnections& inputs, const double & bias)
{
	auto net_value = bias;
	for each (auto& input_neuron in inputs)
	{
		net_value += input_neuron.m_Weight * input_neuron.m_From->GetOutput();
	}
	return net_value;
}

double BackPropNeuronStrategy::FindNewBias(const double & bias, const double & delta)
{
	return bias + m_LearningRate * delta;
}

void BackPropNeuronStrategy::UpdateWeights(TNeuronConnections& connections, const double & delta)
{
	for (int index = 0; index < connections.size(); index++)
	{
		connections[index].m_Weight = connections[index].m_Weight + m_LearningRate * connections[index].m_From->GetOutput() * delta;
	}
}

void BackPropNeuronStrategy::RandomizeWeights(TNeuronConnections & connections)
{
	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(-100, 100);

	for (int index = 0; index < connections.size(); index++)
	{
		connections[index].m_Weight = distribution(generator) / 50.0;
	}
}
