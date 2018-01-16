#ifndef FUZZY_SET_H 
#define FUZZY_SET_H

namespace fuzzy
{
//enum MembershipFunc3
//{
//	NEGATIVE,
//	ZERO,
//	POSITIVE,
//	END
//};
enum MembershipFunc5
{
	NM,
	NS,
	ZE,
	PS,
	PM,
	END
};
static const char* MembershipFunc3String[] = { "NEGATIVE", "ZERO", "POSITIVE" };
static const char* MembershipFunc5String[] = { "NM", "NS","ZE","PS","PM" };

class IFuzzySet
{

public:

	//static double GetCommonValue( const MembershipFunc3 func, const double& min, const double& max )
	//{
	//	double value = 0;
	//	if ( max <= min )
	//	{
	//		return -1;
	//	}
	//	switch ( func )
	//	{
	//	case NEGATIVE:
	//		value = min;
	//		break;
	//	case ZERO:
	//		value = min + ( max - min ) / 2.0;
	//		break;
	//	case POSITIVE:
	//		value = max;
	//		break;
	//	default:
	//		break;
	//	}
	//	return value;
	//};
    static double GetCommonValue( const int func, const double& min, const double& max );

	//static MembershipFunc3 GetFuzzyValue( const double& value, const double& min, const double& max )
	//{
	//	double average = min + ( max - min ) / 2.0;
	//	double to_average = std::abs( value - average );
	//	double to_min = std::abs( value - min );
	//	double to_max = std::abs( value - max );
	//	auto candidat = NEGATIVE;
	//	if ( value > average )
	//	{
	//		if ( to_average < to_max )
	//			candidat = ZERO;
	//		else
	//			candidat = POSITIVE;
	//	}
	//	else
	//	{
	//		if ( to_average < to_min )
	//			candidat = ZERO;
	//		else
	//			candidat = NEGATIVE;
	//	}

	//	return candidat;
	//};

    static MembershipFunc5 GetFuzzyValue( const double& value, const double& min, const double& max );
	virtual double GetValue( const double& ) const = 0;

private:
    static std::vector<double> DivideIntervalOnCount( const double& min, const double& max, const int& count );
    static std::vector<double> DivideIntervalOnCountWithoutEdge( const double& min, const double& max, const int& count );
};

typedef std::shared_ptr<IFuzzySet> IFuzzySetPtr;

class FuzzySet : public IFuzzySet
{
public:
	FuzzySet( const MembershipFunc5& term, const double& min, const double& max )
		: m_Term( term ), m_Min( min ), m_Max( max )
	{};
	double GetValue( const double& ) const override;

	char* ToStr() const;

private:
	MembershipFunc5 m_Term;
	double m_Min;
	double m_Max;
};

typedef std::shared_ptr<FuzzySet> FuzzySetPtr;


class ActivatedFuzzySet : public FuzzySet
{
	typedef FuzzySet base;
public:
	ActivatedFuzzySet( FuzzySet fuzzy_set )
		: base( fuzzy_set )
	{}
	ActivatedFuzzySet( const MembershipFunc5& term, const double& min, const double& max )
		: base( term, min, max )
	{}
	double GetValue( const double& ) const override;
	void SetTruthDegree( const double& );
	double GetTruthDegree() const
	{
		return m_TruthDegree;
	}

private:
	double GetActivatedValue( const double& ) const;

private:
	double m_TruthDegree = -1;
};

class UnionOfFuzzySets : public IFuzzySet
{
public:
	UnionOfFuzzySets()
	{};
	void AddFuzzySet( const IFuzzySetPtr& );
	double GetValue( const double& input_variable ) const override;

private:
	double GetMaxValue( const double& input_value ) const;
private:
	std::vector<IFuzzySetPtr> m_FuzzySets;
};
}
#endif
