#ifndef RULES_BASE_H 
#define RULES_BASE_H

#include "../IceThicknessGenerator.h"

namespace fuzzy
{
class Rule;

class RulesBase
{
public:
	RulesBase()
	{
		m_Rules = std::vector<Rule>();
	};
	RulesBase( const std::vector<Rule>& rules )
		: m_Rules( rules )
	{};
	bool IsEmpty()
	{
		return m_Rules.empty();
	}
	std::vector<Rule> GetRules()
	{
		return m_Rules;
	};

private:
	std::vector<Rule> m_Rules;
};

typedef std::shared_ptr<RulesBase> RulesBasePtr;


class RulesBaseGeneratorForIceThickness
{
public:
	RulesBaseGeneratorForIceThickness( InputParams* params );
	RulesBasePtr GenerateRulesBaseForIceThickness();

private:
	MembershipFunc5 CreateOutputMembershipFunc( const MembershipFunc5& input1, const MembershipFunc5& input2 );
private:

	InputParams* m_Params;
	IceThicknessGenerator* m_Generator;
};
}

#endif
