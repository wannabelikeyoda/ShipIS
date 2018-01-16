#ifndef BACK_PROP_NEURON_STRATEGY_H 
#define BACK_PROP_NEURON_STRATEGY_H

#include "INeuronStrategy.h"

namespace neural
{
class BackPropNeuronStrategy : public INeuronStrategy
{
public:
    BackPropNeuronStrategy( const double& learning_rate );
    double FindDelta( const double & output, const double & error_factor ) override;
    double Activation( const double & value ) override;
    double FindNetValue( const TNeuronConnections& inputs, const double & bias ) override;
    double FindNewBias( const double & bias, const double & delta ) override;
    void UpdateWeights( TNeuronConnections& connections, const double & delta ) override;
    void RandomizeWeights( TNeuronConnections& connections ) override;
private:
    double m_LearningRate = -1.0;
};
typedef std::shared_ptr<BackPropNeuronStrategy> BackPropNeuronStrategyPtr;

}
#endif //BACK_PROP_NEURON_STRATEGY_H