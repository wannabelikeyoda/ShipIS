#ifndef NEURAL_NETWORK_H
#define NEURAL_NETWORK_H

#include "INeuralNetwork.h"

namespace neural
{

class INeuronStrategy;
typedef std::shared_ptr<INeuronStrategy> INeuronStrategyPtr;

class NeuralNetwork : public INeuralNetwork
{
public:
	NeuralNetwork() {}

	INeuralNetworkPtr Clone() const;
	NeuralNetwork(const INeuronStrategyPtr& stratregy, const std::vector<int>& neurons_in_layers);
	void TrainNetwork(const TrainingDataPtr& t_data) override;
	void ConnectNeurons(const INeuronPtr& begin, const INeuronPtr& end) override;
	void ConnectNeurons(INeuronPtr& begin, INeuronPtr& end, const double & weight) override;
	void ConnectAllLayers() override;
	void ConnectLayers(NeuronLayer& layer1, NeuronLayer& layer2) override;
	void ClearParams() override;
	
	TNeuronLayers GetAllLayers() override;
	NeuronLayer GetInputLayer() override;
	NeuronLayer GetOutputLayer() override;
	void RunNetwork(const std::vector<double>& inputs) override;
	std::vector<double> GetOutputValue() override;
	std::vector<int> GetNeuronsInLayers() override;

	double GetError(const TrainingDataPtr& t_data) override;
	void PrintAnswer(const TrainingDataPtr& t_data) override;
	void PrintOutputValues() override;
private:
	TNeuronLayers m_Layers;
};
typedef std::shared_ptr<NeuralNetwork> NeuralNetworkPtr;

}

#endif //NEURAL_NETWORK_H
