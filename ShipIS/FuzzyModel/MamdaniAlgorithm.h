#ifndef MAMDANI_ALGORITHM_H 
#define MAMDANI_ALGORITHM_H

struct InputParams;

namespace fuzzy
{

class RulesBase;
typedef std::shared_ptr<RulesBase> RulesBasePtr;
class ActivatedFuzzySet;
class UnionOfFuzzySets;

class MamdaniAlgorithm
{
public:
    MamdaniAlgorithm( const int& input_variables, const int& output_variables );

    MamdaniAlgorithm( const RulesBasePtr& rules );

    RulesBasePtr GetRulesBase();
	void SetRules( const RulesBasePtr& rules );
	void SetParams( const InputParams* params );
	std::vector<double> Execute( const std::vector<double>& input_data );

private:
	std::vector<double> Fuzzyfication( const std::vector<double>& input_data );
	std::vector<double> Aggregation( const std::vector<double>& fuzzyfied_data );
	std::vector<ActivatedFuzzySet> Activization( const std::vector<double>& aggregated_data );
	std::vector<UnionOfFuzzySets> Accumulation( const std::vector<ActivatedFuzzySet>& activated_data );
	std::vector<double> Defuzzyfication( const std::vector<UnionOfFuzzySets>& activated_data );
	double Integral( const UnionOfFuzzySets& fuzzy_sets, const bool with_value );
	double IntegralSimpson( const UnionOfFuzzySets& fuzzy_sets, const bool with_value );
private:
	RulesBasePtr m_Rules;
	const InputParams* m_Params;
	int m_NumberOfInputVariables = -1;
	int m_NumberOfOutputVariables = -1;
};

}

#endif