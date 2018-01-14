#ifndef CONDITION_H 
#define CONDITION_H

#include "Statement.h"

namespace fuzzy
{
class FuzzySet;

class Condition : public Statement
{
	typedef Statement base;
public:
    Condition( const FuzzySet& fuzzy_set, const int input_variable_id, const std::string& name );
};
}
#endif