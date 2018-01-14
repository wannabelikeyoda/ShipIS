#ifndef RULE_H 
#define RULE_H

namespace fuzzy
{

class Conclusion;
class Condition;
class Rule
{
public:
	Rule( const std::vector<Condition>& conditions, const std::vector<Conclusion>& conclusions )
		: m_Conditions( conditions ), m_Conclusions( conclusions )
	{};
	std::vector<Condition> GetConditions()
	{
		return m_Conditions;
	};
	std::vector<Conclusion> GetConclusions()
	{
		return m_Conclusions;
	};

private:
	std::vector<Condition> m_Conditions;
	std::vector<Conclusion> m_Conclusions;

};

}
#endif
