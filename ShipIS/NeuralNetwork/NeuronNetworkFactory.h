#ifndef NEURON_NETWORK_FACTORY_H
#define NEURON_NETWORK_FACTORY_H

#include "NeuralNetwork.h"
namespace neural
{
class NeuronNetworkFactory
{
public:
    static NeuralNetwork CreateNetwork( const std::vector<int>& neuronsInLayers, const double& learning_rate );
private:

};
}
#endif //NEURON_NETWORK_FACTORY_H
