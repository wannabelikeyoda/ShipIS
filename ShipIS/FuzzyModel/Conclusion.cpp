#include "../stdafx.h"
#include "Conclusion.h"

fuzzy::Conclusion::Conclusion( const FuzzySet& fuzzy_set, const int input_variable_id, const std::string& name )
    : base( fuzzy_set, input_variable_id, name )
{
    m_Weight = 1.0;
};
