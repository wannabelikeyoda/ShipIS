#ifndef NEURAL_NETWORK_HELPER_H
#define NEURAL_NETWORK_HELPER_H

namespace neural
{
class NeuralNetwork;

class TrainingData;
typedef std::shared_ptr<TrainingData> TrainingDataPtr;
typedef std::vector<TrainingDataPtr> TTrainingDataVector;

class INeuralNetwork;
typedef std::shared_ptr<INeuralNetwork> INeuralNetworkPtr;
class NeuralNetworkHelper
{
public:
    NeuralNetworkHelper()
    {}
    NeuralNetworkHelper( const std::vector<int> neurons_in_layers, const double learning_rate, const TTrainingDataVector& training_data_vector = TTrainingDataVector() );

    NeuralNetworkHelper( const NeuralNetwork* network );

    void SetTrainingData( const TTrainingDataVector& training_data_vector );
    double TrainNetwork( const double& accuracy = 0.00001, const int& epoch_count = 1000, const bool auto_learn = false );
    void TestNetwork( const TrainingDataPtr& t_data );
    INeuralNetworkPtr GetNetwork()
    {
        return m_NeuralNetwork;
    }
    void ChangeTrainingDataVector( const TTrainingDataVector& training_data_vector );
private:
    bool CheckTrainingData();
    void ConvertToSigmoidAllData();

private:
    INeuralNetworkPtr m_NeuralNetwork;
    TTrainingDataVector m_TrainingDataVector;
    double m_LearningRate = -1.0;
};
typedef std::shared_ptr<NeuralNetworkHelper> NeuralNetworkHelperPtr;
}

#endif // NEURAL_NETWORK_HELPER_H
