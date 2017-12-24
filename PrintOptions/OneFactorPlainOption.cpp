#ifndef ONEFACTORPLAINOPTION_CPP
#define ONEFACTORPLAINOPTION_CPP

#include "OneFactorPlainOption.hpp"
#include "Option.hpp"

#include <cmath>
#include <sstream>
#include <vector>
#include <exception>
#include <iostream>

using namespace std;

//Option optzz = Option();
//Default constructor
OneFactorPlainOption::OneFactorPlainOption() : m_T(1), m_b(1), m_modeltype("Black_Scholes_Stock"), Option(){}

//Full parameter constructor
OneFactorPlainOption::OneFactorPlainOption(double S, double K, double r, double o, double T, string modeltype) : 
	 m_T(T), m_modeltype(modeltype), Option(S, K, r, o){

	//Set cost of carry
	SetCostOfCarry();
}

//Copy unique variables
void OneFactorPlainOption::copy(const OneFactorPlainOption& o2)
{
	m_T = o2.m_T;
	m_b = o2.m_b;
	m_modeltype = o2.m_modeltype;
}


//Copy constructor calls base class constructor
OneFactorPlainOption::OneFactorPlainOption(const OneFactorPlainOption& o2) : Option(o2.S(), o2.K(),o2.r(), o2.o())
{ 
	copy(o2);
}

OneFactorPlainOption& OneFactorPlainOption::operator = (const OneFactorPlainOption& option2)
{

	if (this == &option2) return *this;

	copy(option2);

	return *this;
}


//Setters
void OneFactorPlainOption::T(double T){
	m_T = T;
};

void OneFactorPlainOption::modeltype(string modeltype) {
	m_modeltype = modeltype;

	//Set cost of carry
	SetCostOfCarry();
};

void OneFactorPlainOption::r(double r) {
	Option::r(r);

	//Set cost of carry
	SetCostOfCarry();
};

//Getters
double OneFactorPlainOption::T() const{
	return m_T;
};
string OneFactorPlainOption::modeltype() const {
	return m_modeltype;
};
double OneFactorPlainOption::b() const {
	return m_b;
};
double OneFactorPlainOption::r() const {
	return Option::r();
};

//Set cost of carry based on model type
//Since cost of carry changes depending on the parameters, it cannot be directly set
void OneFactorPlainOption::SetCostOfCarry() {

	if (m_modeltype == "Black_Scholes_Stock") {
		m_b = r();
	}
	else if (m_modeltype == "Black_Scholes_Future") {
		m_b = 0;
	}

}

//<<Operator Overloading Functions
std::ostream& operator << (std::ostream& stream, const OneFactorPlainOption& opt) {

	stream << "OneFactorPlainOption(S=" << opt.S() << ",K=" << opt.K() << ",r=" << opt.r() << ",o=" << opt.o() << ",T=" << opt.m_T;
	stream << ",b=" << opt.m_b << ",model=" << opt.m_modeltype << ")";
	return stream;
}

//Calculate Call Price
double OneFactorPlainOption::CallPrice() const{

	double firstHalf = S()*exp((m_b - r())*m_T)*N(D1());
	double secondHalf = K() * exp(-r()*m_T) * N(D2());

	return firstHalf - secondHalf;
}

//Calculate Put Price
double OneFactorPlainOption::PutPrice() const{

	double firstHalf = K() * exp(-r()*m_T) * N(-D2());
	double secondHalf = S() * exp((m_b - r())*m_T) * N(-D1());

	return firstHalf - secondHalf;
}

//Calculate Put Parity Price
double OneFactorPlainOption::PutParityPrice() const{
	return CallPrice() + K() * exp(-r() * m_T) - S();
}

//Calculate Call Parity Price
double OneFactorPlainOption::CallParityPrice() const{
	return PutPrice() + S() - K() * exp(-r() * m_T);
}

//Calculate Distributions
double OneFactorPlainOption::n(double x) const{

	double A = 1.0 / sqrt(2.0 * 3.1415);
	return A * exp(-x*x*0.5);

}

//Calculate Delta Sensitivity
double OneFactorPlainOption::CallDelta() const{
	double p1, p2;

	p1 = exp((m_b - r())*m_T);
	p2 = N(D1());

	return p1 * p2;

}

double OneFactorPlainOption::PutDelta() const{
	
	return  exp((m_b - r())*m_T) * - (N(D1())- 1);
}

//Calculate Gamma Sensitivity
double OneFactorPlainOption::Gamma() const{
	double p1, p2;
	
	p1 = n(D1())*exp((m_b - r())*m_T);
	p2 = S() * o() * sqrt(m_T);

	return p1 / p2;
}

//Calculate the Gamma Apporximation
double OneFactorPlainOption::DeltaDivDiff(double h, string type) const{

	//Check h is big enough for accuracy
	if (h < 1 / pow(10, 12)) {
		throw h;
	}

	OneFactorPlainOption optionInc = *this;
	optionInc.S(S() + h);
	OneFactorPlainOption optionDec = *this;
	optionDec.S(S() - h);

	if (type == "Call") {
		return (optionInc.CallDelta() - optionDec.CallDelta()) / (2 * h);
	}
	else {
		return (optionInc.PutDelta() - optionDec.PutDelta()) / (2 * h);
	}
}

//Calculate the Delta Apporximation
double OneFactorPlainOption::GammaDivDiff(double h) const {

	//Check h is big enough for accuracy
	if (h < 1 / pow(10, 12)) {
		throw h;
	}

	OneFactorPlainOption optionInc = *this;
	optionInc.S(S() + h);
	OneFactorPlainOption optionDec = *this;
	optionDec.S(S() - h);

	return (optionInc.Gamma() - 2 * this->Gamma() + optionDec.Gamma()) / pow(h,2);

}

double OneFactorPlainOption::N(double x) const{ 

	// The approximation to the cumulative normal distribution
	double a1 = 0.4361836;
	double a2 = -0.1201676;
	double a3 = 0.9372980;

	double k = 1.0 / (1.0 + (0.33267 * x));

	if (x >= 0.0)
	{
		return 1.0 - n(x)* (a1*k + (a2*k*k) + (a3*k*k*k));
	}
	else
	{
		return 1.0 - N(-x);
	}

}

//Calculate d1
double OneFactorPlainOption::D1() const{
	
	double num = log(S() / K()) +(m_b + pow(o(), 2) / 2) * m_T;
	double den = o() * sqrt(m_T);

	return num / den;
}

//Calculate d2
double OneFactorPlainOption::D2() const{
	return D1() - (o() * sqrt(m_T));
}

//Destructor
OneFactorPlainOption::~OneFactorPlainOption() {}

#endif