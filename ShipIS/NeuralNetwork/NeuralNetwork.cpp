#include "NeuralNetwork.h"
#include "Neuron.h"

INeuralNetworkPtr NeuralNetwork::Clone() const
{
	return std::make_shared<NeuralNetwork>(*this);
}

NeuralNetwork::NeuralNetwork(const INeuronStrategyPtr& stratregy, const std::vector<int>& neurons_in_layers)
{
	for each (auto& neurons_count in neurons_in_layers)
	{
		NeuronLayer layer = NeuronLayer();
		for (int i = 0; i < neurons_count; i++)
		{
			layer.Neurons.push_back(std::make_shared<Neuron>(stratregy));
		}
		m_Layers.push_back(layer);
	}
}

void NeuralNetwork::TrainNetwork(const TrainingDataPtr& t_data)
{
	//t_data->PrintInputValues();
	RunNetwork(t_data->GetInputValues());
	auto& output_layer = GetOutputLayer();
	//Find delta of output layer
	for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(output_layer); index_neuron++)
	{
		auto& this_neuron = NeuronLayer::GetNeuronByIndex(output_layer, index_neuron);
		auto data_output_value = t_data->GetOutputValueByIndex(index_neuron);
		this_neuron->UpdateDelta( data_output_value - this_neuron->GetOutput());
		//std::cout << "Ideal: " << data_output_value << " Calculated: " << this_neuron->GetOutput() << " Delta: " << this_neuron->GetDelta() << "\n";
	}
	//Find delta of hidden layers
	for (int index_layer = m_Layers.size() - 2; index_layer > 0; index_layer--)
	{
		auto& curr_layer = m_Layers[index_layer];
		for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(curr_layer); index_neuron++)
		{
			double error_factor = 0;
			auto& some_neuron = NeuronLayer::GetNeuronByIndex(curr_layer, index_neuron);

			for each (auto& connected_neuron in some_neuron->ForwardNeurons())
			{
				auto& input_neurons = connected_neuron->Inputs();
				for each (auto& input_connection in input_neurons)
				{
					if (input_connection.m_From == some_neuron)
					{
						error_factor += connected_neuron->GetDelta() * input_connection.m_Weight;
						break;
					}
				}
			}

			some_neuron->UpdateDelta(error_factor);
		}

	}

	//Update free params
	for each (auto& layer in m_Layers)
	{
		for each (auto& neuron in layer.Neurons)
		{
			neuron->UpdateFreeParams();
		}
	}
}

double NeuralNetwork::GetError(const TrainingDataPtr& t_data)
{
	auto& output_layer = GetOutputLayer();
	double error_value = 0.0;
	//Find error of output layer
	for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(output_layer); index_neuron++)
	{
		auto& this_neuron = NeuronLayer::GetNeuronByIndex(output_layer, index_neuron);
		auto data_output_value = t_data->GetOutputValueByIndex(index_neuron);
		error_value += (data_output_value - this_neuron->GetOutput())*(data_output_value - this_neuron->GetOutput());
	}
	error_value /= NeuronLayer::NeuronLayerLength(output_layer);
	//std::cout << "Error: " << error_value << "\n\n";
	return error_value;
}

void NeuralNetwork::PrintAnswer(const TrainingDataPtr& t_data)
{
	t_data->PrintInputValues();
	t_data->PrintOutputValues();
	RunNetwork(t_data->GetInputValues());
	PrintOutputValues();
}

void NeuralNetwork::PrintOutputValues()
{
	auto& output_layer = GetOutputLayer();

	for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(output_layer); index_neuron++)
	{
		auto& this_neuron = NeuronLayer::GetNeuronByIndex(output_layer, index_neuron);
		std::cout << "Output value " << (index_neuron + 1) << " "<< this_neuron->GetOutput() << " ";
	}
	std::cout << '\n';
}
void NeuralNetwork::ConnectNeurons(const INeuronPtr& begin, const INeuronPtr& end)
{
	NeuronConnection neuron_connection = NeuronConnection(begin, end);
	begin->AddForwardNeuron(end);
	end->AddInputNeuron(neuron_connection);
}

void NeuralNetwork::ConnectNeurons(INeuronPtr& begin, INeuronPtr& end, const double & weight)
{
	NeuronConnection neuron_connection = NeuronConnection(begin, end, weight);
}

void NeuralNetwork::ConnectAllLayers()
{
	for (int index_layer = 0; index_layer < m_Layers.size()-1; index_layer++)
	{
		ConnectLayers(m_Layers[index_layer], m_Layers[index_layer + 1]);
	}
}

void NeuralNetwork::ConnectLayers(NeuronLayer& layer1, NeuronLayer& layer2)
{
	for (int index_layer1 = 0; index_layer1 < NeuronLayer::NeuronLayerLength(layer1); index_layer1++)
	{
		for (int index_layer2 = 0; index_layer2 < NeuronLayer::NeuronLayerLength(layer2); index_layer2++)
		{
			ConnectNeurons(NeuronLayer::GetNeuronByIndex(layer1, index_layer1), NeuronLayer::GetNeuronByIndex(layer2, index_layer2));
		}
	}
}

void NeuralNetwork::ClearParams()
{
	for (int index_layer = 0; index_layer < m_Layers.size(); index_layer++)
	{
		auto& curr_layer = m_Layers[index_layer];
		for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(curr_layer); index_neuron++)
		{
			NeuronLayer::GetNeuronByIndex(curr_layer, index_neuron)->ClearParams();
		}
	}
}

TNeuronLayers NeuralNetwork::GetAllLayers()
{
	return m_Layers;
}

NeuronLayer NeuralNetwork::GetInputLayer()
{
	return m_Layers[0];
}

NeuronLayer NeuralNetwork::GetOutputLayer()
{
	return m_Layers[m_Layers.size() -1];
}

void NeuralNetwork::RunNetwork(const std::vector<double>& inputs)
{

	auto& input_layer = GetInputLayer();
	if (inputs.size() != NeuronLayer::NeuronLayerLength(input_layer))
	{
		std::cout << "Invalid Input values!";
		return;
	}
	for(int index = 0; index < NeuronLayer::NeuronLayerLength(input_layer); index++)
	{
		NeuronLayer::GetNeuronByIndex(input_layer, index)->SetOutput(inputs[index]);
	}

	for (int index_layer = 1; index_layer < m_Layers.size(); index_layer++)
	{
		auto& curr_layer = m_Layers[index_layer];
		for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(curr_layer); index_neuron++)
		{
			NeuronLayer::GetNeuronByIndex(curr_layer, index_neuron)->UpdateOutput();
		}
	}
}

std::vector<double> NeuralNetwork::GetOutputValue()
{
	auto& output_layer = GetOutputLayer();
	std::vector<double> values;
	for (int index_neuron = 0; index_neuron < NeuronLayer::NeuronLayerLength(output_layer); index_neuron++)
	{
		values.push_back(NeuronLayer::GetNeuronByIndex(output_layer, index_neuron)->GetOutput());
	}
	return values;
}

std::vector<int> NeuralNetwork::GetNeuronsInLayers()
{
	std::vector<int> neurons_in_layers;
	for (int index_layer = 0; index_layer < m_Layers.size(); index_layer++)
	{
		neurons_in_layers.push_back(NeuronLayer::NeuronLayerLength(m_Layers[index_layer]));
	}
	return neurons_in_layers;
}
