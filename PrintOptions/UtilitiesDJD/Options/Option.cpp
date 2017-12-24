#ifndef OPTION_CPP
#define OPTION_CPP

#include "Option.hpp"

#include <cmath>
#include <sstream>
#include <vector>
#include <exception>
#include <iostream>

using namespace std;


//Default constructor
Option::Option() : m_S(1), m_K(2), m_r(.01), m_o(1){
}

//Full Parameter Constructor
Option::Option(double S, double K, double r, double o) :
	m_S(S), m_K(K), m_r(r), m_o(o){

}

//Copy
void Option::copy(const Option& o2)
{
	m_r = o2.m_r;
	m_S = o2.m_S;
	m_K = o2.m_K;
	m_o = o2.m_o;
}

// Copy constructor
Option::Option(const Option& o2)
{
	copy(o2);
}

//Getters
void Option::S(double S) {
	m_S = S;
};
void Option::K(double K) {
	m_K = K;
};
void Option::r(double r) {
	m_r = r;
};
void Option::o(double o) {
	m_o = o;
};

//Setters
double Option::S() const {
	return m_S;
};
double Option::K() const {
	return m_K;
};
double Option::r() const {
	return m_r;
};
double Option::o() const {
	return m_o;
};

//Operater Overloading Functions
Option& Option::operator = (const Option& option2)
{

	if (this == &option2) return *this;

	copy(option2);

	return *this;
}

std::ostream& operator << (std::ostream& stream, const Option& opt) {

	stream << "Option(S=" << opt.m_S << ",K=" << opt.m_K << ",r=" << opt.m_r << ",o=" << opt.m_o << ")";
	return stream;
}

//Destructor
Option::~Option() {}



#endif