// UnitTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <igloo/igloo.h>
#include "../NeuralLib/NeuralNetwork/NeuralNetwork.h"
#include "../NeuralLib/NeuralNetwork/Neuron.h"
#include "../NeuralLib/NeuralNetwork/NeuronConnection.h"
#include "../NeuralLib/NeuralNetwork/TrainingData.h"
#include "../NeuralLib/NeuralNetwork/NeuralNetworkHelper.h"

using namespace igloo;
using namespace neural;


Context(NeuralNetworkContructor)
{
    Spec(DefaultConstructorWorksFine)
    {
        const std::vector<int> neurons_in_layers = { 2,2,2 };
        const double learning_rate = 0.5;
        //auto network = new NeuralNetwork();
        auto helper = new neural::NeuralNetworkHelper( neurons_in_layers, learning_rate );
        //auto neural_network = new neural::NeuralNetwork();
        Assert::That( helper->GetNetwork()->GetInputLayer().Neurons[0]->GetBias(), Equals( 0 ) );
    }
};

int main( int argc, const char* argv[] )
{
    auto result = igloo::TestRunner::RunAllTests( argc, argv );
    std::system( "pause" );
    return result;
}

