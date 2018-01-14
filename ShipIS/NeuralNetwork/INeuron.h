#ifndef I_NEURON_H 
#define I_NEURON_H

namespace neural
{
class INeuron;
typedef std::shared_ptr<INeuron> INeuronPtr;
typedef std::vector<INeuronPtr> TNeurons;

class NeuronConnection;
typedef std::vector<NeuronConnection> TNeuronConnections;

class INeuronStrategy;
typedef std::shared_ptr<INeuronStrategy> INeuronStrategyPtr;

class INeuron
{
public:
    virtual double GetBias() = 0;
    virtual double GetDelta() = 0;
    virtual double GetOutput() = 0;
    virtual void SetOutput( const double& output_val ) = 0;
    virtual TNeuronConnections Inputs() = 0;
    virtual TNeurons ForwardNeurons() = 0;
    virtual INeuronStrategyPtr Strategy() = 0;

    virtual void UpdateOutput() = 0;
    virtual void UpdateDelta( const double& error_factor ) = 0;
    virtual void UpdateFreeParams() = 0;
    virtual void ClearParams() = 0;
    virtual void AddForwardNeuron( const INeuronPtr& neuron ) = 0;
    virtual void AddInputNeuron( const NeuronConnection& connection ) = 0;
};
}


#endif // I_NEURON_H 

