#ifndef ONEFACTORPLAINPRICING_HPP
#define ONEFACTORPLAINPRICING_HPP

#include "Option.hpp"
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class OneFactorPlainOption : public Option  {

private:
	
	double m_T, m_b;
	string m_modeltype;
	
	//Copy function
	void copy(const OneFactorPlainOption& o2);

	//Private Calculations
	void SetCostOfCarry(); //Determines b
	double n(double) const; //Cumulative distribution
	double N(double) const; //Cumulative distribution
	double D1() const; //finds d1
	double D2() const; //finds d2


public:
	//Constructors
	OneFactorPlainOption();
	OneFactorPlainOption(double, double, double, double, double, string);
	OneFactorPlainOption(const OneFactorPlainOption& option2);	// Copy constructor

	//Setters
	void T(double);
	void modeltype(string);
	void r(double); //override
	
	//Getters
	double T() const;
	string modeltype() const;
	double b() const;
	double r() const; //override
	

	//Calculate Methods
	double CallPrice() const;
	double PutPrice() const;
	double CallParityPrice() const;
	double PutParityPrice() const;
	double CallDelta() const;
	double PutDelta() const;
	double Gamma() const;
	double DeltaDivDiff(double, string) const;
	double GammaDivDiff(double) const;

	//Operator overloads
	virtual OneFactorPlainOption& operator = (const OneFactorPlainOption& option2);
	friend std::ostream& operator << (std::ostream&, const OneFactorPlainOption&);

	//Destructor
	~OneFactorPlainOption();

};

#endif



