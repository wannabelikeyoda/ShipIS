#ifndef ICE_THICKNESS_GENERATOR_H 
#define ICE_THICKNESS_GENERATOR_H 

class TrainingData;
typedef std::shared_ptr<TrainingData> TrainingDataPtr;
typedef std::vector<TrainingDataPtr> TTrainingDataVector;

class IceThicknessGenerator
{
public:
	IceThicknessGenerator(const double& max_value, const double& average_value);
	double Next();

private:
	double m_AverageValue = -1;
	double m_MaxValue = -1;
	double m_CurrentValue = -1;
};
typedef std::shared_ptr<IceThicknessGenerator> IceThicknessGeneratorPtr;

class GeneratorTrainingForIceThickness
{
public:
	GeneratorTrainingForIceThickness(const IceThicknessGeneratorPtr& generator, InputParams& params);

	TTrainingDataVector GenerateTrainingVector(const int& count);

private:
	IceThicknessGeneratorPtr m_IceThicknessGenerator;
	InputParams& m_Params;
};

#endif