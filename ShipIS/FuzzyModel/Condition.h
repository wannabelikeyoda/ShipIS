#ifndef CONDITION_H 
#define CONDITION_H
#include <string>
namespace fuzzy
{
class Statement;
class FuzzySet;

class Condition : public Statement
{
	typedef Statement base;
public:
	Condition( const FuzzySet& fuzzy_set, const int& input_variable_id, const std::string& name )
		: base( fuzzy_set, input_variable_id, name )
	{};
};
}
#endif