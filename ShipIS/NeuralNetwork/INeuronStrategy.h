#ifndef I_NEURON_STRATEGY_H 
#define I_NEURON_STRATEGY_H

#include "NeuronConnection.h"

class NeuronConnection;
typedef std::vector<NeuronConnection> TNeuronConnections;

class INeuronStrategy
{
public:
	virtual double FindDelta(const double& output, const double& error_factor) = 0;
	virtual double Activation(const double& value) = 0;
	virtual double FindNetValue(const TNeuronConnections& inputs, const double& bias) = 0;
	virtual double FindNewBias(const double& bias, const double& delta) = 0;
	virtual void UpdateWeights(TNeuronConnections& connections, const double& delta) = 0;
	virtual void RandomizeWeights(TNeuronConnections& connections) = 0;

};
typedef std::shared_ptr<INeuronStrategy> INeuronStrategyPtr;


#endif // I_NEURON_STRATEGY_H 
