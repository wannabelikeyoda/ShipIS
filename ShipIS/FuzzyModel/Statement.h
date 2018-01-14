#ifndef STATEMENT_H 
#define STATEMENT_H

#include "FuzzySet.h"
#include <string>
namespace fuzzy
{
class Statement
{
public:
	Statement( const FuzzySet& fuzzy_set, const int& input_variable_id, const std::string& name )
		: m_FuzzySet( fuzzy_set ), m_InputVariableId( input_variable_id ), m_VariableName(name)
	{};

	int GetVariable()
	{
		return m_InputVariableId;
	}
	FuzzySet GetFuzzySet()
	{
		return m_FuzzySet;
	}
	std::string ToStr() const
	{
		std::string str;
		str += m_VariableName;
		str += " is ";
		str += m_FuzzySet.ToStr();
		return str;
	}

private:
	FuzzySet m_FuzzySet;
	int m_InputVariableId;
	std::string m_VariableName;
};
}
#endif