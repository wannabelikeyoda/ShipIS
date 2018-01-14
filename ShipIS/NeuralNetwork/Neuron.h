#ifndef NEURON_H 
#define NEURON_H

#include "INeuron.h"
#include "BackPropNeuronStrategy.h"

namespace neural
{
class Neuron : public INeuron
{

public:
    Neuron()
    {};
    Neuron( const INeuronStrategyPtr & strategy );
    void UpdateOutput() override;
    void UpdateDelta( const double& error_factor ) override;
    void UpdateFreeParams() override;
    void ClearParams() override;
    void AddForwardNeuron( const INeuronPtr& neuron ) override;
    void AddInputNeuron( const NeuronConnection& connection ) override;

    double GetBias() override
    {
        return m_Bias;
    }
    double GetDelta() override
    {
        return m_Delta;
    }
    double GetOutput() override
    {
        return m_Output;
    }
    void SetOutput( const double& output_val ) override
    {
        m_Output = output_val;
    }
    TNeuronConnections Inputs() override
    {
        return m_Inputs;
    }
    TNeurons ForwardNeurons() override
    {
        return m_ForwardNeurons;
    }
    INeuronStrategyPtr Strategy() override
    {
        return m_Strategy;
    }

private:
    double m_Bias = -1.0;
    double m_Delta = -1.0;
    double m_Output = -1.0;
    TNeuronConnections m_Inputs;
    TNeurons m_ForwardNeurons;
    INeuronStrategyPtr m_Strategy;
};
typedef std::shared_ptr<Neuron> NeuronPtr;
}
#endif
