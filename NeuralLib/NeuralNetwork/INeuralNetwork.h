#ifndef I_NEURAL_NETWORK_H
#define I_NEURAL_NETWORK_H


namespace neural
{
class NeuronLayer;
typedef std::vector<NeuronLayer> TNeuronLayers;

class INeuron;
typedef std::shared_ptr<INeuron> INeuronPtr;

class TrainingData;
typedef std::shared_ptr<TrainingData> TrainingDataPtr;

class INeuralNetwork;
typedef std::shared_ptr<INeuralNetwork> INeuralNetworkPtr;

class INeuralNetwork
{
public:
    virtual INeuralNetworkPtr Clone() const = 0;
    virtual void TrainNetwork( const TrainingDataPtr& t_data ) = 0;
    virtual void ConnectNeurons( const INeuronPtr& begin, const INeuronPtr& end ) = 0;
    virtual void ConnectNeurons( INeuronPtr& begin, INeuronPtr& end, const double& weight ) = 0;
    virtual void ConnectAllLayers() = 0;
    virtual void ConnectLayers( NeuronLayer& layer1, NeuronLayer& layer2 ) = 0;
    virtual void RunNetwork( const std::vector<double>& inputs ) = 0;
    virtual std::vector<double> GetOutputValue() = 0;

    virtual void ClearParams() = 0;
    virtual TNeuronLayers GetAllLayers() = 0;
    virtual NeuronLayer GetInputLayer() = 0;
    virtual NeuronLayer GetOutputLayer() = 0;
    virtual std::vector<int> GetNeuronsInLayers() = 0;
    virtual double GetError( const TrainingDataPtr& t_data ) = 0;
    virtual void PrintAnswer( const TrainingDataPtr& t_data ) = 0;
    virtual void PrintOutputValues() = 0;
};

}

#endif // I_NEURAL_NETWORK_H

