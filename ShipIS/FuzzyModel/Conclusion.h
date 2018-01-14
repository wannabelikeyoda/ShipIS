#ifndef CONCLUSION_H 
#define CONCLUSION_H

#include "Statement.h"

namespace fuzzy
{
class Conclusion : public Statement
{
	typedef Statement base;
public:
    Conclusion( const FuzzySet& fuzzy_set, const int input_variable_id, const std::string& name );
	double GetWeight()
	{
		return m_Weight;
	};
	void SetWeight( const double& );
private:
	double m_Weight = -1;
};

}
#endif
