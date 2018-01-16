#ifndef TRAINING_DATA_H
#define TRAINING_DATA_H
namespace neural
{

class TrainingData
{
public:
    TrainingData( const std::vector<double>& input, const std::vector<double>& output );
    void PrintInputValues();
    void PrintOutputValues();
    std::vector<double>& GetInputValues();
    double GetOutputValueByIndex( const int& index );

private:
    std::vector<double> m_InputValues;
    std::vector<double> m_OutputValues;
};

typedef std::shared_ptr<TrainingData> TrainingDataPtr;
typedef std::vector<TrainingDataPtr> TTrainingDataVector;

class TrainingDataVectorFactory
{
public:
    static TTrainingDataVector GenerateRandomTrainingDataVector( const int& count_datas = 10 );

    static TTrainingDataVector GenerateTrainingDataVector4( const std::vector<double>& input1,
        const std::vector<double>& input2,
        const std::vector<double>& input3,
        const std::vector<double>& input4,
        const std::vector<double>& output );
};

}

#endif //TRAINING_DATA_H
