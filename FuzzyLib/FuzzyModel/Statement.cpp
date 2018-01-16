#include "../stdafx.h"
#include "Statement.h"
#include "FuzzySet.h"

namespace fuzzy
{

Statement::Statement( const FuzzySet & fuzzy_set, const int input_variable_id, const std::string & name )
    : m_FuzzySet( std::make_shared<FuzzySet>( fuzzy_set ) )
    , m_InputVariableId( input_variable_id ), m_VariableName( name )
{}

std::string Statement::ToStr() const
{
    std::string str;
    str += m_VariableName;
    str += " is ";
    str += m_FuzzySet->ToStr();
    return str;
}

FuzzySetPtr Statement::GetFuzzySet()
{
    return m_FuzzySet;
}
}