#include "../stdafx.h"
#include "TrainingData.h"
#include "NeuralNetwork.h"
#include "NeuralNetworkHelper.h"
#include "NeuronNetworkFactory.h"


namespace neural
{
NeuralNetworkHelper::NeuralNetworkHelper( const std::vector<int> neurons_in_layers,  const double learning_rate, const TTrainingDataVector& training_data_vector )
    : m_LearningRate( learning_rate ),
    m_TrainingDataVector( training_data_vector )
{
    if ( !CheckTrainingData() )
    {
        std::cout << "TrainingData has values out of range [0;1]" << " We convert all data to this condition\n"; // TODO: remove everywhere cout 
    }
    m_NeuralNetwork = std::make_shared<NeuralNetwork>( NeuronNetworkFactory::CreateNetwork( neurons_in_layers, learning_rate ) );
}


NeuralNetworkHelper::NeuralNetworkHelper( const NeuralNetwork* network )
{
    m_NeuralNetwork = std::make_shared<NeuralNetwork>( *network );
}

void NeuralNetworkHelper::SetTrainingData( const TTrainingDataVector& training_data_vector )
{
    m_TrainingDataVector = TTrainingDataVector( training_data_vector );
    if ( !CheckTrainingData() )
    {
        std::cout << "TrainingData has values out of range [0;1]" << " We convert all data to this condition\n"; // TODO: remove everywhere cout 
    }
}

double NeuralNetworkHelper::TrainNetwork( const double& accuracy, const int& epoch_count, const bool auto_learn )
{
    double max_error = 1.0;
    int count_errors = 0;
    bool inc_learning_rate = true;
    INeuralNetworkPtr training_network = m_NeuralNetwork->Clone();
    for ( int epoch_index = 0; epoch_index < epoch_count; epoch_index++ )
    {
        double max_error_previous = max_error;
        max_error = 0.0;
        std::cout << "Epoch " << ( epoch_index + 1 ) << "\n\n";

        for each ( TrainingDataPtr data in m_TrainingDataVector )
        {
            training_network->TrainNetwork( data );
            double curr_err = training_network->GetError( data );
            max_error = max_error < curr_err ? curr_err : max_error;
        }

        if ( max_error > ( max_error_previous - 0.00000001 ) )
        {
            count_errors++;

            if ( count_errors < 100 && auto_learn )
            {
                std::cout << "Change learning rate" << "\n\n";
                if ( m_LearningRate > 1.0 )
                    inc_learning_rate = false;

                if ( m_LearningRate < 0.01 )
                    inc_learning_rate = true;

                m_LearningRate = inc_learning_rate ? m_LearningRate + m_LearningRate / 20.0 :
                    m_LearningRate - m_LearningRate / 20.0;

                //training_network = m_NeuralNetwork->Clone();
            }
            else
            {
                count_errors = 0;
                training_network->ClearParams();
            }
            epoch_index = -1;
        }
        else
        {
            m_NeuralNetwork = training_network->Clone();
            count_errors = 0;
        }

        std::cout << "Max Error in Epoch: " << max_error << "\n";
        if ( max_error < accuracy )
        {
            break;
        }
    }
    std::cout << "Out condition\n";
    return max_error;
}

void NeuralNetworkHelper::TestNetwork( const TrainingDataPtr& t_data )  //TODO: Test not only print the answer
{
    m_NeuralNetwork->PrintAnswer( t_data );
}

void NeuralNetworkHelper::ChangeTrainingDataVector( const TTrainingDataVector& training_data_vector )
{
    m_TrainingDataVector = TTrainingDataVector( training_data_vector );
}

bool NeuralNetworkHelper::CheckTrainingData()
{
    for each ( TrainingDataPtr data in m_TrainingDataVector )
    {
        for each ( const double& value in data->GetInputValues() )
        {
            if ( value > 1.0 || value < 0.0 )
            {
                ConvertToSigmoidAllData();
                return false;
            }
        }
    }
    return true;
}

void NeuralNetworkHelper::ConvertToSigmoidAllData()
{
    for each ( TrainingDataPtr data in m_TrainingDataVector )
    {
        auto& values = data->GetInputValues();
        for ( int index = 0; index < data->GetInputValues().size(); index++ )
        {
            values[index] = 1 / ( 1 + exp( -values[index] ) );
        }
    }
}
}