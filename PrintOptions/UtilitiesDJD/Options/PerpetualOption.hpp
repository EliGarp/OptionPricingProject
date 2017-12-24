#ifndef PERPETUALOPTION_HPP
#define PERPETUALOPTION_HPP

#include "Option.hpp"

#include <string>

using namespace std;

class PerpetualOption : public Option {

private:
	double m_b;

	//Copy function
	void copy(const PerpetualOption& o2);

	//Set y1 or y2
	double y1() const;
	double y2() const;

public:

	//Constructors
	PerpetualOption();
	PerpetualOption(double, double, double, double, double);
	PerpetualOption(const PerpetualOption& option2); // Copy constructor

	//Setter
	void b(double);

	//Getter
	double b() const;

	//Calculate Methods
	double CallPrice() const;
	double PutPrice() const;


	//Operator overloads
	virtual PerpetualOption& operator = (const PerpetualOption& option2);
	friend std::ostream& operator << (std::ostream&, const PerpetualOption&);

	//Destructor
	~PerpetualOption();

	
};





#endif
