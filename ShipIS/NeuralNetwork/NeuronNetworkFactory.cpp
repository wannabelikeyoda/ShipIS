#include "NeuronNetworkFactory.h"
#include "NeuralNetwork.h"
#include "BackPropNeuronStrategy.h"
namespace neural
{

NeuralNetwork NeuronNetworkFactory::CreateNetwork( const std::vector<int>& neurons_in_layers, const double& learning_rate )
{
    auto strategy = BackPropNeuronStrategy( learning_rate );

    auto network = NeuralNetwork( std::make_shared<BackPropNeuronStrategy>( strategy ), neurons_in_layers );
    network.ConnectAllLayers();
    return NeuralNetwork( network );
}
}