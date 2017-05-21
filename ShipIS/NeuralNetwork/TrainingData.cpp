#include "TrainingData.h"
;
TrainingData::TrainingData(const std::vector<double>& input, const std::vector<double>& output)
	: m_InputValues(input), m_OutputValues(output)
{}

void TrainingData::PrintInputValues()
{
	int i = 1;
	for each (auto& value in m_InputValues)
	{
		std::cout << "Input value " << i << " : " << value << " ";
		i++;
	}
	std::cout << '\n';
}

void TrainingData::PrintOutputValues()
{
	int i = 1;
	for each (auto& value in m_OutputValues)
	{
		std::cout << "Ideal Output value " << i << " : " << value << " ";
		i++;
	}
	std::cout << '\n';
}

std::vector<double>& TrainingData::GetInputValues()
{
	return m_InputValues;
}

double TrainingData::GetOutputValueByIndex(const int & index)
{
	if (index < m_OutputValues.size())
	{
		return m_OutputValues[index];
	}
	else
	{
		std::cout << "Invalid index!\n";
	}
	return 0;
}

TTrainingDataVector TrainingDataVectorFactory::GenerateRandomTrainingDataVector(const int& count_datas)
{
	TTrainingDataVector data_vector;

	std::vector<double> input_vector;
	std::vector<double> output_vector;

	std::vector<double> i_vector;
	std::vector<double> j_vector;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<int> distribution(0, 15);

	for (int index = 0; index < count_datas; index++)
	{
		i_vector.push_back(distribution(generator) / 10.0);
		j_vector.push_back(i_vector[index] / 3.0);

		input_vector = { i_vector[index], j_vector[index] };
		output_vector = { abs(std::sin(i_vector[index] + j_vector[index])) + 0.0 };
		auto data = std::make_shared<TrainingData>(input_vector, output_vector);

		data_vector.push_back(data);
	}
	return data_vector;
}

TTrainingDataVector TrainingDataVectorFactory::GenerateTrainingDataVector4(const std::vector<double>& input1,
																			const std::vector<double>& input2,
																			const std::vector<double>& input3,
																			const std::vector<double>& input4,
																			const std::vector<double>& output)
{

	TTrainingDataVector data_vector;

	std::vector<double> input_vector;
	std::vector<double> output_vector;

	for (int i = 0; i < input1.size(); i++)
	{
		input_vector = { input1[i],input2[i],input3[i] ,input4[i] };
		output_vector = { output[i] };
		auto data = std::make_shared<TrainingData>(input_vector, output_vector);

		data_vector.push_back(data);
	}
	return data_vector;
}