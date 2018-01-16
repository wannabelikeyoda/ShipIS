#include "../stdafx.h"
#include "MamdaniAlgorithm.h"
#include "Rule.h"
#include "../InputParams.h"
#include "FuzzySet.h"
#include "RulesBase.h"
#include "Condition.h"
#include "Conclusion.h"

namespace fuzzy
{
MamdaniAlgorithm::MamdaniAlgorithm( const int & input_variables, const int & output_variables )
{
    m_Rules = std::make_shared<RulesBase>();
    m_NumberOfInputVariables = input_variables;
    m_NumberOfOutputVariables = output_variables;
}

MamdaniAlgorithm::MamdaniAlgorithm( const RulesBasePtr & rules )
    : m_Rules( rules )
{}
RulesBasePtr MamdaniAlgorithm::GetRulesBase()
{
    return m_Rules;
}
void MamdaniAlgorithm::SetRules( const RulesBasePtr& rules )
{
    m_Rules = rules;
}

void MamdaniAlgorithm::SetParams( const InputParams* params )
{
    m_Params = params;
}

std::vector<double> MamdaniAlgorithm::Execute( const std::vector<double>& input_data )
{
    if ( m_Rules->IsEmpty() )
    {
        std::vector<double> dummy;
        for ( int i = 0; i < m_NumberOfOutputVariables; i++ )
        {
            dummy.push_back( 0 );
        }
        return dummy;
    }

    auto& fuzzyfied_data = Fuzzyfication( input_data );
    auto& aggregated_data = Aggregation( fuzzyfied_data );
    auto& activizated_data = Activization( aggregated_data );
    auto& accumulated_data = Accumulation( activizated_data );
    return Defuzzyfication( accumulated_data );
}

std::vector<double> MamdaniAlgorithm::Fuzzyfication( const std::vector<double>& input_data )
{
    std::vector<double> fuzzyfied_data;
    for ( Rule& rule : m_Rules->GetRules() )
    {
        for ( Condition condition : rule.GetConditions() )
        {
            int j = condition.GetVariable();
            FuzzySet term = ( *condition.GetFuzzySet() );
            fuzzyfied_data.push_back( term.GetValue( input_data[j] ) );
        }
    }
    return fuzzyfied_data;
}

std::vector<double> MamdaniAlgorithm::Aggregation( const std::vector<double>& fuzzyfied_data )
{
    int i = 0;
    std::vector<double> aggregated_data;
    for ( Rule rule : m_Rules->GetRules() )
    {
        double truthOfConditions = 1.0;
        for ( Condition condition : rule.GetConditions() )
        {
            truthOfConditions = ( truthOfConditions < fuzzyfied_data[i] ) ? truthOfConditions : fuzzyfied_data[i];   //min
            i++;
        }
        aggregated_data.push_back( truthOfConditions );
    }
    return aggregated_data;
}

std::vector<ActivatedFuzzySet> MamdaniAlgorithm::Activization( const std::vector<double>& aggregated_data )
{
    int i = 0;
    std::vector<ActivatedFuzzySet> activatedFuzzySets;
    for ( Rule rule : m_Rules->GetRules() )
    {
        for ( Conclusion conclusion : rule.GetConclusions() )
        {
            auto temp = aggregated_data[i] * conclusion.GetWeight();
            ActivatedFuzzySet activatedFuzzySet = (ActivatedFuzzySet)( *conclusion.GetFuzzySet() );
            activatedFuzzySet.SetTruthDegree( temp );
            activatedFuzzySets.push_back( activatedFuzzySet );
            i++;
        }
    }
    return activatedFuzzySets;
}

std::vector<UnionOfFuzzySets> MamdaniAlgorithm::Accumulation( const std::vector<ActivatedFuzzySet>& activated_data )
{
    std::vector<UnionOfFuzzySets> unionsOfFuzzySets = std::vector<UnionOfFuzzySets>( m_NumberOfOutputVariables );
    int i = 0;
    for ( Rule rule : m_Rules->GetRules() )
    {
        for ( Conclusion conclusion : rule.GetConclusions() )
        {
            int id = conclusion.GetVariable();
            if ( activated_data[i].GetTruthDegree() > 0.0 ) // Tsukamoto rule
            {
                unionsOfFuzzySets[id].AddFuzzySet( std::make_shared<ActivatedFuzzySet>( activated_data[i] ) );
            }
            i++;
        }
    }
    return unionsOfFuzzySets;
}

std::vector<double> MamdaniAlgorithm::Defuzzyfication( const std::vector<UnionOfFuzzySets>& accumulated_data )
{
    std::vector<double> defuzzufied_result;
    for ( int i = 0; i < m_NumberOfOutputVariables; i++ )
    {
        //double i1 = Integral( accumulated_data[i], true );
        //double i2 = Integral( accumulated_data[i], false );
        //defuzzufied_result.push_back( i1 / i2 );

        double i3 = IntegralSimpson( accumulated_data[i], true );
        double i4 = IntegralSimpson( accumulated_data[i], false );
        defuzzufied_result.push_back( i3 / i4 );

    }
    return defuzzufied_result;
}

double MamdaniAlgorithm::Integral( const UnionOfFuzzySets& fuzzy_sets, const bool with_value )
{
    double S = 0;
    double begin_x = 0, end_x = m_Params->max_velocity;
    double x = begin_x;
    double n = 100;

    double dx = ( end_x - begin_x ) / ( n + 0.0 );

    for ( int i = 0; i < n; i++ )
    {
        x += dx;
        S += with_value ? fuzzy_sets.GetValue( x ) * x : fuzzy_sets.GetValue( x );
    }
    return S;
}

double MamdaniAlgorithm::IntegralSimpson( const UnionOfFuzzySets& fuzzy_sets, const bool with_value )
{
    double I;
    double h;
    double x;
    double a = 0, b = m_Params->max_velocity; // a- нижня грацница интегрирования, b - верхняя граница интегрирования
    int m = 10; // точность интегирования ( кол-во промежутков разбиения )

    h = ( b - a ) / ( m + 0.0 );
    x = a;

    I = fuzzy_sets.GetValue( a ) * ( with_value ? x : 1 );
    int n = 0;

    while ( n < m - 1 )
    {
        x = x + h;
        if ( n % 2 == 0 )
            I += 4 * fuzzy_sets.GetValue( x ) * ( with_value ? x : 1 );
        else
            I += 2 * fuzzy_sets.GetValue( x ) * ( with_value ? x : 1 );
        n++;
    }
    I += fuzzy_sets.GetValue( b ) * ( with_value ? x : 1 );

    return I*h / 3.0;
}

}
