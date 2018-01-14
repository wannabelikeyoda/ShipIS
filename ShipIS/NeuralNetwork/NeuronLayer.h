#ifndef NEURON_LAYER_H
#define NEURON_LAYER_H

namespace neural
{
class INeuron;
typedef std::shared_ptr<INeuron> INeuronPtr;
typedef std::vector<INeuronPtr> TNeurons;
class NeuronLayer
{
public:
    TNeurons Neurons;

    static int NeuronLayerLength( const NeuronLayer& layer )
    {
        return layer.Neurons.size();
    }

    static INeuronPtr& GetNeuronByIndex( NeuronLayer& layer, const int& index )
    {
        return layer.Neurons[index];
    }
};
typedef std::vector<NeuronLayer> TNeuronLayers;

}


#endif //NEURON_LAYER_H
