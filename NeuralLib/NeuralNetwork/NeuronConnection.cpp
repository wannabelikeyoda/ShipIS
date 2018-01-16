#include "../stdafx.h"
#include "NeuronConnection.h"

namespace neural
{
NeuronConnection::NeuronConnection( const INeuronPtr& begin, const INeuronPtr& end )
    : m_From( begin ), m_To( end )
{
    std::random_device device;
    std::mt19937 generator( device() );
    std::uniform_int_distribution<int> distribution( -100, 100 );

    m_Weight = distribution( generator ) / 50.0;
}
NeuronConnection::NeuronConnection( INeuronPtr & begin, INeuronPtr & end, const double & weight )
    : m_From( begin ), m_To( end ), m_Weight( weight )
{}
}