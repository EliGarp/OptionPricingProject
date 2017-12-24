#ifndef OPTION_HPP
#define OPTION_HPP

#include <sstream>

class Option {

private:
	double m_S, m_K, m_r, m_o;

	//Copy
	void copy(const Option& op2);

public:
	//Constructors
	Option();
	Option(double, double, double, double);
	Option(const Option& option2);	// Copy constructor

	//Setters
	void S(double);
	void K(double);
	void r(double);
	void o(double);

	//Getters
	double S() const;
	double K() const;
	double r() const;
	double o() const;

	//Operator Overloading Functions
	Option& operator = (const Option& option2);//(const Option& option2)
	friend std::ostream& operator << (std::ostream& stream, const Option& opt);


	//Destructor
	virtual ~Option();
};

#endif
