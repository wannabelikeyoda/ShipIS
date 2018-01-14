#ifndef MAMDANI_ALGORITHM_H 
#define MAMDANI_ALGORITHM_H

#include "../stdafx.h"
#include "RulesBase.h"

namespace fuzzy
{
class MamdaniAlgorithm
{
public:
	MamdaniAlgorithm( const int& input_variables, const int& output_variables )
	{
		m_Rules = std::make_shared<RulesBase>();
		m_NumberOfInputVariables = input_variables;
		m_NumberOfOutputVariables = output_variables;
	}

	MamdaniAlgorithm( const RulesBasePtr& rules )
		: m_Rules( rules )
	{}
	RulesBasePtr GetRulesBase()
	{
		return m_Rules;
	}
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