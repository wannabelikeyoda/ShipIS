#ifndef STATEMENT_H 
#define STATEMENT_H

namespace fuzzy
{
class FuzzySet;
typedef std::shared_ptr<FuzzySet> FuzzySetPtr;

class Statement
{
public:
    Statement( const FuzzySet& fuzzy_set, const int input_variable_id, const std::string& name );
    
    int GetVariable()
    {
        return m_InputVariableId;
    }
    FuzzySetPtr GetFuzzySet();
    std::string ToStr() const;

private:
    FuzzySetPtr m_FuzzySet;
    int m_InputVariableId;
    std::string m_VariableName;
};
}
#endif