#ifndef NEURON_CONNECTION_H
#define NEURON_CONNECTION_H

#include "stdafx.h"

class INeuron;
typedef std::shared_ptr<INeuron> INeuronPtr;

class NeuronConnection
{
public:
	NeuronConnection(const INeuronPtr& begin, const INeuronPtr& end);
	NeuronConnection(INeuronPtr & begin, INeuronPtr & end, const double & weight);


	INeuronPtr m_From;
	INeuronPtr m_To;
	double m_Weight = -1;
};
typedef std::vector<NeuronConnection> TNeuronConnections;


#endif //NEURON_CONNECTION_H