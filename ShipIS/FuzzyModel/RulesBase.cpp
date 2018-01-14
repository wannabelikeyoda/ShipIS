#include "RulesBase.h"
#include "FuzzySet.h"
#include "Rule.h"

namespace fuzzy
{
RulesBaseGeneratorForIceThickness::RulesBaseGeneratorForIceThickness( InputParams * params )
{
	m_Params = params;
}
//Conditions:
//0-ice thick
//1-snow thick
//Conclustions:
//0-ship velocity
//
RulesBasePtr RulesBaseGeneratorForIceThickness::GenerateRulesBaseForIceThickness()
{
	std::vector<Rule> rules = std::vector<Rule>();
	unsigned i = MembershipFunc5::NM;
	while ( i < MembershipFunc5::END )
	{
		unsigned j = MembershipFunc5::NM;
		while ( j < MembershipFunc5::END )
		{
			std::vector<Condition> conditions;
			std::vector<Conclusion> conclusions;

			conditions.push_back( Condition( FuzzySet( MembershipFunc5( i ), 0, m_Params->max_ice_thick ), 0, std::string( "ice thick" ) ) );
			conditions.push_back( Condition( FuzzySet( MembershipFunc5( j ), 0, m_Params->max_snow_thick ), 1, std::string( "snow thick" ) ) );

			MembershipFunc5 output_func = CreateOutputMembershipFunc( MembershipFunc5( i ), MembershipFunc5( j ) );

			conclusions.push_back( Conclusion( FuzzySet( output_func, 0, m_Params->max_velocity ), 0, std::string( "ship velocity" ) ) );

			rules.push_back( Rule( conditions, conclusions ) );
			j++;
		}
		i++;
	}
	return std::make_shared<RulesBase>( rules );
}

MembershipFunc5 RulesBaseGeneratorForIceThickness::CreateOutputMembershipFunc( const MembershipFunc5 input1, const MembershipFunc5 input2 )
{
	double input_common1 = IFuzzySet::GetCommonValue( input1, 0, m_Params->max_ice_thick );
	double input_common2 = IFuzzySet::GetCommonValue( input2, 0, m_Params->max_snow_thick );
	double math_velocity = MathVelocityCalculator::CalculateVelocitySimple( input_common1, input_common2, *m_Params );
	return IFuzzySet::GetFuzzyValue( math_velocity, 0, m_Params->max_velocity );
}


}