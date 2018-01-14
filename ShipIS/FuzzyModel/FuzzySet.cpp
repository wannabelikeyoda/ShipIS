#include "../stdafx.h"
#include "FuzzySet.h"
#include <algorithm>

namespace fuzzy
{
double FuzzySet::GetValue( const double& input_variable ) const
{
	double value = 0;
	if ( m_Max <= m_Min )
	{
		return 0;
	}
	double max_value_term = GetCommonValue( m_Term, m_Min, m_Max );
	if ( input_variable < max_value_term && m_Term == MembershipFunc5::NM )
		return 1;

	if ( input_variable > max_value_term && m_Term == MembershipFunc5::PM )
		return 1;

	double step = ( m_Max - m_Min ) / 4.0;
	if ( std::abs( max_value_term - input_variable ) > step )
	{
		return 0;
	}
	if ( input_variable > max_value_term )
	{
		value = ( -1 ) / step * ( input_variable - max_value_term ) + 1;
	}
	else
	{
		value = 1 / step * ( input_variable - max_value_term ) + 1;
	}
	/*double step = ( m_Max - m_Min ) / 6;
	switch ( m_Term )
	{
	case MembershipFunc3::NEGATIVE:
		if ( input_variable < m_Min + step )
			value = 1;
		else if ( input_variable < m_Min + 2 * step )
			value = (-1) / step * (input_variable - step) + 1;
		else
			value = 0;
		break;
	case MembershipFunc3::ZERO:
		if ( input_variable < m_Min + step || input_variable > m_Min + 5 * step )
			value = 0;
		else if ( input_variable < m_Min + 3 * step )
			value = 1 / ( 2.0 * step ) * ( input_variable - 3 * step ) + 1;
		else
			value = ( -1 ) / ( 2.0 * step ) * ( input_variable - 3 * step ) + 1;
		break;
	case MembershipFunc3::POSITIVE:
		if ( input_variable > m_Min + 5 * step )
			value = 1;
		else if ( input_variable > m_Min + 4 * step )
			value = 1 / step * (input_variable - 5 * step ) + 1;
		else
			value = 0;
		break;
	default:
		break;
	}*/
	return value;

}

char* FuzzySet::ToStr() const
{
	return const_cast<char*>( MembershipFunc5String[m_Term] );
}

double ActivatedFuzzySet::GetValue( const double& input_variable ) const
{
	return GetActivatedValue( input_variable );
}

double ActivatedFuzzySet::GetActivatedValue( const double&  input_variable ) const
{
	return std::min( base::GetValue( input_variable ), m_TruthDegree );
}

void ActivatedFuzzySet::SetTruthDegree( const double& truth_degree )
{
	m_TruthDegree = truth_degree;
}

void UnionOfFuzzySets::AddFuzzySet( const IFuzzySetPtr& fuzzy_set )
{
	m_FuzzySets.push_back( fuzzy_set );
}

double UnionOfFuzzySets::GetValue( const double& input_variable ) const
{
	return GetMaxValue( input_variable );
}

double UnionOfFuzzySets::GetMaxValue( const double & input_value ) const
{
	double result = 0.0;
	for ( IFuzzySetPtr fuzzy_set : m_FuzzySets )
	{
		result = std::max( result, fuzzy_set->GetValue( input_value ) );
	}
	return result;
}
}