#include "../stdafx.h"
#include "Condition.h"

fuzzy::Condition::Condition( const FuzzySet& fuzzy_set, const int input_variable_id, const std::string& name )
    : base( fuzzy_set, input_variable_id, name )
{
};
