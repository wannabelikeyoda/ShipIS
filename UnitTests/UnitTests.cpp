// UnitTests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <igloo/igloo.h>
#include "../NeuralLib/NeuralNetwork/Neuron.h"
#include "../NeuralLib/NeuralNetwork/NeuronConnection.h"
#include "../NeuralLib/NeuralNetwork/TrainingData.h"
#include "../NeuralLib/NeuralNetwork/NeuralNetwork.h"
#include "../NeuralLib/NeuralNetwork/NeuralNetworkHelper.h"
#include "../NeuralLib/NeuralNetwork/NeuronNetworkFactory.h"
#include "../NeuralLib/NeuralNetwork/BackPropNeuronStrategy.h"

using namespace igloo;
using namespace neural;



Context( TrainingDataUnitTest )
{
    TrainingDataUnitTest()
    {
        training_data = std::make_shared<TrainingData>( std::vector<double>( { 1,2,3 } ), std::vector<double>( { 3,2,1 } ) );
    }

    Spec( ConstructorWorksFine )
    {
        if ( !training_data )
        {
            Assert::Failure( "ConstructorWorksFine fails" );
        }
    }

    Spec( GetOutputValueByIndexTest )
    {
        Assert::That( training_data->GetOutputValueByIndex( 0 ), Equals( 3 ) );
        Assert::That( training_data->GetOutputValueByIndex( 1 ), Equals( 2 ) );
        Assert::That( training_data->GetOutputValueByIndex( 2 ), Equals( 1 ) );
        Assert::That( training_data->GetOutputValueByIndex( 4 ), Is().Not().GreaterThan( 0 ) );
    }

    TrainingDataPtr training_data;
};

Context( BackPropNeuronStrategyTest )
{
    BackPropNeuronStrategyPtr strategy;
    void SetUp()
    {
        strategy = std::make_shared<BackPropNeuronStrategy>( 0.5 );
    }

    Spec( ConstructorWorksFine )
    {
        if ( !strategy )
        {
            Assert::Failure( "ConstructorWorksFine fails" );
        }
    }

    Spec( FuctionFindDeltaTest )
    {
        //output * ( 1 - output ) * error_factor;
        Assert::That( strategy->FindDelta( 1, 0.3 ), Equals( 0 ) );
        Assert::That( strategy->FindDelta( 2, 0.5 ), Equals( 2 * ( 1 - 2 ) * 0.5 ) );
        Assert::That( strategy->FindDelta( 3, 0.8 ), Equals( 3 * ( 1 - 3 ) * 0.8 ) );
        Assert::That( strategy->FindDelta( 4, 3 ), Equals( 4 * ( 1 - 4 ) * 3 ) );
        Assert::That( strategy->FindDelta( 5, 0 ), Equals( 5 * ( 1 - 5 ) * 0 ) );
        Assert::That( strategy->FindDelta( 6, -3.5 ), Equals( 6 * ( 1 - 6 ) * -3.5 ) );
        Assert::That( strategy->FindDelta( 7, 1 ), Equals( 7 * ( 1 - 7 ) * 1 ) );
    }

    Spec( FuctionActivationTest )
    {
        // 1 / ( 1 + exp( -value ) );
        Assert::That( strategy->Activation( 2.5 ), Equals( 1 / ( 1 + exp( -2.5 ) ) ) );
        Assert::That( strategy->Activation( 8 ), Equals( 1 / ( 1 + exp( -8 ) ) ) );
        Assert::That( strategy->Activation( -1 ), Equals( 1 / ( 1 + exp( 1 ) ) ) );
        Assert::That( strategy->Activation( 0 ), Equals( 1 / ( 1 + exp( 0 ) ) ) );
        Assert::That( strategy->Activation( 1000 ), Equals( 1 / ( 1 + exp( -1000 ) ) ) );
        Assert::That( strategy->Activation( 3.14 ), Equals( 1 / ( 1 + exp( -3.14 ) ) ) );
        Assert::That( strategy->Activation( 2.78 ), Equals( 1 / ( 1 + exp( -2.78 ) ) ) );
    }
};

Context( NeuronTest )
{

    NeuronPtr neuron;
    BackPropNeuronStrategyPtr strategy = std::make_shared<BackPropNeuronStrategy>( 0.8 );

    void SetUp()
    {
        strategy = std::make_shared<BackPropNeuronStrategy>( 0.8 );
        neuron = std::make_shared<Neuron>( strategy );
    }

    Spec( ConstructorWorksFine )
    {
        if ( !neuron )
        {
            Assert::Failure( "ConstructorWorksFine fails" );
        }
    }

    Spec( AddInputNeuronTest )
    {
        auto other_neuron = std::make_shared<Neuron>( strategy );
        auto connection = NeuronConnection( neuron, other_neuron );
        neuron->AddInputNeuron( connection );
    }

    Spec( UpdateOutputTest )
    {
        neuron->UpdateOutput();
        Assert::That( neuron->GetOutput(), Equals( 0.5 ) );
    }

    Spec( UpdateDeltaTest )
    {
        neuron->UpdateDelta( 0.3 );
        Assert::That( neuron->GetDelta(), Equals( -0.6 ) );
    }
};

Context( NeuralNetworkTest )
{

    NeuralNetworkPtr network_for_test;
    BackPropNeuronStrategyPtr strategy = std::make_shared<BackPropNeuronStrategy>( 0.8 );

    void SetUp()
    {
        const std::vector<int> neurons_in_layers = { 2,2,1 };
        network_for_test = std::make_shared<NeuralNetwork>( strategy, neurons_in_layers );
    }

    Spec( DefaultConstructorWorksFine )
    {
        if ( !new NeuralNetwork() )
        {
            Assert::Failure( "DefaultConstructorWorksFine fails" );
        }
    }

    Spec( ConstructorWorksFine )
    {
        if ( !network_for_test )
        {
            Assert::Failure( "ConstructorWorksFine fails" );
        }
    }

    Spec( TrainNetworkTest )
    {
        auto training_data1 = std::make_shared<TrainingData>( std::vector<double>( { 1,0 } ), std::vector<double>( { 1 } ) );
        auto training_data2 = std::make_shared<TrainingData>( std::vector<double>( { 0,0 } ), std::vector<double>( { 0 } ) );
        auto training_data3 = std::make_shared<TrainingData>( std::vector<double>( { 0,1 } ), std::vector<double>( { 1 } ) );
        auto training_data4 = std::make_shared<TrainingData>( std::vector<double>( { 1,1 } ), std::vector<double>( { 0 } ) );

        auto before_error = network_for_test->GetError( training_data1 );
        before_error += network_for_test->GetError( training_data2 );
        before_error += network_for_test->GetError( training_data3 );
        before_error += network_for_test->GetError( training_data3 );
        before_error /= 4;

        network_for_test->TrainNetwork( training_data1 );
        network_for_test->TrainNetwork( training_data2 );
        network_for_test->TrainNetwork( training_data3 );
        network_for_test->TrainNetwork( training_data4 );


        auto after_error = network_for_test->GetError( training_data1 );
        after_error += network_for_test->GetError( training_data2 );
        after_error += network_for_test->GetError( training_data3 );
        after_error += network_for_test->GetError( training_data3 );
        after_error /= 4;

        Assert::That( after_error, Is().LessThan( before_error ) );

    }

    Spec( ConnectAllLayersTest )
    {
        network_for_test->ConnectAllLayers();

        if ( network_for_test->GetAllLayers().empty() || network_for_test->GetInputLayer().Neurons.empty() || network_for_test->GetInputLayer().Neurons[0]->ForwardNeurons().empty() )
        {
            Assert::Failure( "ConnectAllLayersTest fails" );
        }
    }
};

int main( int argc, const char* argv[] )
{
    auto result = igloo::TestRunner::RunAllTests( argc, argv );
    std::system( "pause" );
    return result;
}

