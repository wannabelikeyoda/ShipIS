#include "../stdafx.h"
#include "FuzzySet.h"

namespace fuzzy
{

double IFuzzySet::GetCommonValue( const int func, const double& min, const double& max )
{
    double value = 0;
    if ( max <= min )
    {
        return -1;
    }
    std::vector<double> divided_values = DivideIntervalOnCountWithoutEdge( min, max, 5 );

    return divided_values[func];
};

MembershipFunc5 IFuzzySet::GetFuzzyValue( const double& value, const double& min, const double& max )
{
    std::vector<double> divided_values = DivideIntervalOnCountWithoutEdge( min, max, 5 );
    for ( auto i = 0; i < (int)divided_values.size(); i++ )
    {
        if ( value < divided_values[i] )
        {
            if ( i == 0 )
                return MembershipFunc5( i );

            double to_more = std::abs( value - divided_values[i] );
            double to_less = std::abs( value - divided_values[i - 1] );

            if ( to_less < to_more )
                return MembershipFunc5( i - 1 );
            else
                return MembershipFunc5( i );
        }
    }
    return MembershipFunc5( divided_values.size() - 1 );

}

std::vector<double> IFuzzySet::DivideIntervalOnCount( const double& min, const double& max, const int& count )
{
    std::vector<double> divided_values;
    double step = ( max - min ) / ( count + 1.0 );
    for ( int i = 1; i <= count; i++ )
    {
        divided_values.push_back( min + i*step );
    }
    return divided_values;
}

std::vector<double> IFuzzySet::DivideIntervalOnCountWithoutEdge( const double& min, const double& max, const int& count )
{
    std::vector<double> divided_values;
    double step = ( max - min ) / ( count - 2.0 );
    for ( int i = 0; i <= count; i++ )
    {
        divided_values.push_back( min + i*step );
    }
    return divided_values;
}

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

double ActivatedFuzzySet::GetActivatedValue( const double& input_variable ) const
{
    return ( base::GetValue( input_variable ) < m_TruthDegree ) ? base::GetValue( input_variable ) : m_TruthDegree;   //min
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

double UnionOfFuzzySets::GetMaxValue( const double& input_value ) const
{
	double result = 0.0;
	for ( IFuzzySetPtr fuzzy_set : m_FuzzySets )
	{
		result = ( fuzzy_set->GetValue( input_value ) > result ) ? fuzzy_set->GetValue( input_value ) : result;    //max
	}
	return result;
}
}