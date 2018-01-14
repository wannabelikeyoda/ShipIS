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

	static double GetCommonValue( const int func, const double& min, const double& max )
	{
		double value = 0;
		if ( max <= min )
		{
			return -1;
		}
		std::vector<double> divided_values = DivideIntervalOnCountWithoutEdge( min, max, 5 );

		return divided_values[func];
	};

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

	static MembershipFunc5 GetFuzzyValue( const double& value, const double& min, const double& max )
	{
		std::vector<double> divided_values = DivideIntervalOnCountWithoutEdge( min, max, 5 );
		for ( auto i = 0; i < (int) divided_values.size(); i++ )
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

	};
	virtual double GetValue( const double& ) const = 0;

private:
	static std::vector<double> DivideIntervalOnCount( const double& min, const double& max, const int& count )
	{
		std::vector<double> divided_values;
		double step = ( max - min ) / ( count + 1.0 );
		for ( int i = 1; i <= count; i++ )
		{
			divided_values.push_back( min + i*step );
		}
		return divided_values;
	}

	static std::vector<double> DivideIntervalOnCountWithoutEdge( const double& min, const double& max, const int& count )
	{
		std::vector<double> divided_values;
		double step = ( max - min ) / ( count - 2.0 );
		for ( int i = 0; i <= count; i++ )
		{
			divided_values.push_back( min + i*step );
		}
		return divided_values;
	}

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
