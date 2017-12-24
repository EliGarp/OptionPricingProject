#ifndef PERPETUALOPTION_CPP
#define PERPETUALOPTION_CPP

#include "PerpetualOption.hpp"

#include <cmath>
#include <sstream>
#include <vector>
#include <exception>
#include <iostream>

using namespace std;


//Default constructor
PerpetualOption::PerpetualOption() : Option() {}

//Full parameter constructor
PerpetualOption::PerpetualOption(double S, double K, double r, double o, double b) : 
	m_b(b), Option(S, K, r, o) {}

void PerpetualOption::copy(const PerpetualOption& o2)
{
	m_b = o2.m_b;

}


PerpetualOption::PerpetualOption(const PerpetualOption& o2) : Option(o2.S(), o2.K(), o2.r(), o2.o())
{ // Copy constructor

	copy(o2);
}

PerpetualOption& PerpetualOption::operator = (const PerpetualOption& option2)
{

	if (this == &option2) return *this;

	copy(option2);

	return *this;
}

//Setters
void PerpetualOption::b(double b) {
	m_b = b;
}

//Getters
double PerpetualOption::b() const{
	return m_b;
}

//<<Operator Overloading Functions
std::ostream& operator << (std::ostream& stream, const PerpetualOption& opt) {

	stream << "PerpetualOption(S=" << opt.S() << ",K=" << opt.K() << ",r=" << opt.r() << ",o=" << opt.o() << ",b=" << opt.m_b << ")";
	return stream;
}

//Calculate Call Price
double PerpetualOption::CallPrice() const{
	double y, p1, p2;

	//Set y
	y = y1();

	p1 = K()/(y-1);
	p2 = ((y - 1) / y) * (S() / K());

	return p1 * pow(p2,y);
}

//Calculate Put Price
double PerpetualOption::PutPrice() const{

	double y, p1, p2;

	//Set y
	y = y2();

	p1 = K() / (1 - y);
	p2 = ((y - 1) / y) * (S() / K());

	return p1 * pow(p2, y);
}

double PerpetualOption::y1() const {

	double p1, p2, p3, p3_1, p3_2;

	p1 = .5;
	p2 = m_b / pow(o(), 2);
	p3_1 = pow(p2 - .5, 2);
	p3_2 = (2 * r()) / pow(o(), 2);
	p3 = sqrt(p3_1 + p3_2);

	return p1 - p2 + p3;
}

//Calculate y2
double PerpetualOption::y2() const{

	double p1, p2, p3, p3_1, p3_2;

	p1 = .5;
	p2 = b() / pow(o(), 2);
	p3_1 = pow(p2 - .5, 2);
	p3_2 = (2 * r()) / pow(o(), 2);
	p3 = sqrt(p3_1 + p3_2);

	return p1 - p2 - p3;

}

//Destructor
PerpetualOption::~PerpetualOption() {}

#endif